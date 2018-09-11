//
// Created by admin on 2018/9/6.
//

#include <algorithm>
#include "ManiaRuleset.h"
#include "KeyIO.h"
#include "BeatmapDecoder.h"
#include "GameJudgement.h"

using namespace nso;

double ManiaPlaytimeData::getFrameTime() {
    return frameTime;
}

EdpTimer* ManiaPlaytimeData::getTimer() {
    return timer;
}

void ManiaPlaytimeData::update(double time) {
    if (timer->isRunning()) {
        MKeyFrame->update(time); //更新键盘状态
        frameTime = time;
    }
}

void ManiaPlaytimeData::startJudge() {

}

void ManiaPlaytimeData::endJudge() {
    if (timer->isRunning()) {
        MKeyFrame->endFrame();
    }
}


ManiaDrawdata::ManiaDrawdata(nso::Beatmap &beatmap) : Preempt(500), LineCount((int) (beatmap.CircleSize + 0.01)) {
    beats.insert(beats.begin(), beatmap.controlPoints.Beats.begin(), beatmap.controlPoints.Beats.end());
}

namespace mania{
    bool sortfunc(PlayingHitObject *i, PlayingHitObject *j){
        return i->getTime() < j->getTime();
    }
}

void ManiaDrawdata::prepare() {
    sort(rawObjects.begin(), rawObjects.end(), mania::sortfunc);
    objectsToAdd.clear();
    objectsToAdd.insert(objectsToAdd.end(), rawObjects.begin(), rawObjects.end());
    objectsUsing.clear();
}

void ManiaDrawdata::update(double time) {
    //添加
    double preShowTime = time + Preempt;
    while (!objectsToAdd.empty()) {
        PlayingHitObject *object = objectsToAdd.front();
        if (object->getTime() <= preShowTime) {
            onShowObject(object);
            objectsUsing.push_back(object);
            objectsToAdd.pop_front();
        } else {
            break;
        }
    }

    //舍弃不需要了的物件
    ForEachLong(objectsUsing, it, vector<PlayingHitObject*>::iterator) {
        PlayingHitObject *object = *it;
        if (object->isReleased()) {
            onHideObject(object);
            it = objectsUsing.erase(it);
            it--;
        } else if (object->getFinalTime() < time) {
            object->release();
            onHideObject(object);
            it = objectsUsing.erase(it);
            it--;
        }
    }

    //开始组织数据
    datas.clear();
    ForEachLong(objectsUsing, it, vector<PlayingHitObject*>::iterator) {
        PlayingHitObject *object = *it;
        if (object->getType() == HitObject::TYPE_MANIA_HOLD) {
            float t = (object->getTime() - (float) time) / Preempt;
            t = Clamp(0, t, 1);
            float t2 = (object->getEndTime() - (float) time) / Preempt;
            t2 = Clamp(0, t2, 1);
            datas.push_back(ManiaDrawdataNode{
                    object,
                    object->getType(),
                    ManiaUtil::positionToLine(object->getX(), LineCount),
                    t,
                    t2
            });
        } else {
            float t = (object->getTime() - (float) time) / Preempt;
            t = Clamp(0, t, 1);
            datas.push_back(ManiaDrawdataNode{
                    object,
                    object->getType(),
                    ManiaUtil::positionToLine(object->getX(), LineCount),
                    t,
                    t
            });
        }
    }

    beatsAvalible.clear();
    while ((!beats.empty()) && beats.front() < time) {
        beats.pop_front();
    }
    ForEachLong(beats,itr,list<double>::iterator) {
        if (*itr < time + Preempt) {
            beatsAvalible.push_back((*itr - time) / Preempt);
        } else {
            break;
        }
    }
}

ManiaDrawdata::ManiaDrawdata() {

}

PlayingHitObject::PlayingHitObject(HitObject &h) :
        released(false),
        X(h.x),
        Y(h.y),
        Time(h.time),
        Type(h.type),
        HitSound(h.hitSound) {

}


void ManiaGame::prepareGame() {
    BeatmapDecoder decoder(*OsuFile);
    OsuBeatmap = new Beatmap;
    try {
        decoder.parse(*OsuBeatmap);
        EdpFile songFile(*SetDirectory, OsuBeatmap->AudioFilename);
        SongChannel = new EdpBassChannel(songFile);
        GameKeyFrame = new KeyFrame();

        OsuBeatmap->loadMore();
        OsuBeatmap->controlPoints.generateBeats(-2000, SongChannel->length() + 5000);

        PlayingData = new ManiaPlaytimeData();
        PlayingData->setMKeyFrame(GameKeyFrame);
        PlayingData->setTimer(SongChannel);

        Score = new ManiaScore(OsuBeatmap);
        PlayingData->setScore(Score);


        int keyCount = (int) (OsuBeatmap->CircleSize + 0.001);

        //连接键位
        vector<int> *keyBindings = (*(Setting->getKeyBinding()))[keyCount - 1];
        ForI(key, 0, keyCount){
            KeyHolder *holder = new KeyHolder();
            GameKeyFrame->registerHolder((*keyBindings)[key], holder);
            PlayingData->getKeys().push_back(holder);
        }

        Objects = new vector<ManiaObject*>();

        ForEachLong(OsuBeatmap->hitobjects,itr,vector<HitObject*>::iterator) {
            HitObject *object = *itr;
            if ((object->type & HitObject::TYPE_MASK) == HitObject::TYPE_MANIA_HOLD) {
                ManiaHoldObject *holdObject = new ManiaHoldObject(&((ManiaHold &) *object), OsuBeatmap);
                Objects->push_back(holdObject);
            } else {
                ManiaNoteObject *noteObject = new ManiaNoteObject(&((HitCircle &) *object), OsuBeatmap);
                Objects->push_back(noteObject);
            }
        }

        Judgementer = new GameJudgement<ManiaPlaytimeData>(PlayingData);
        Drawdata = new ManiaDrawdata(*OsuBeatmap);

        vector<JudgeableObject<ManiaPlaytimeData> *> *judges = new vector<JudgeableObject<ManiaPlaytimeData> *>();

        ForEachLong(*Objects,itr,vector<ManiaObject*>::iterator) {
            //DebugL("");
            ManiaObject *object = *itr;
            //DebugL("");
            object->addPlayingObjects(judges, Drawdata->rawObjectsPointer());
            //DebugL("");
        }

        Judgementer->setJudgeObjects(judges);

        Drawdata->prepare();

        Judgementer->prepare();

    } catch (DecodeException &e) {
        throw e;
    }
}

void ManiaGame::linkKeyInput(KeyInput *in) {
    GameKeyFrame->setKeyInput(in);
}

void ManiaGame::runGame() {
    //SongChannel->play();
    SongChannel->postStart(2500);
}

void ManiaGame::pauseGame() {
    SongChannel->pause();
}

void ManiaGame::stopGame() {
    SongChannel->stop();
}

bool ManiaGame::updateTime() {
    SongChannel->update();
    if (SongChannel->isPlaying()) {
        FrameTime = SongChannel->getTime();
        return true;
    } else {
        return false;
    }
}

void ManiaGame::update() {
    if (SongChannel->isPlaying()) {
        PlayingData->update(FrameTime);

        Judgementer->update();

        Drawdata->update(PlayingData->getFrameTime());
    }


}

void ManiaGame::endUpdate() {

}

void ManiaGame::reset() {
    pauseGame();


    Score = new ManiaScore(OsuBeatmap);
    PlayingData->setScore(Score);

    Judgementer = new GameJudgement<ManiaPlaytimeData>(PlayingData);
    Drawdata = new ManiaDrawdata(*OsuBeatmap);

    vector<JudgeableObject<ManiaPlaytimeData> *> *judges = new vector<JudgeableObject<ManiaPlaytimeData> *>();

    ForEachLong(*Objects,itr,vector<ManiaObject*>::iterator) {
        ManiaObject *object = *itr;
        object->addPlayingObjects(judges, Drawdata->rawObjectsPointer());
    }

    Judgementer->setJudgeObjects(judges);
    Drawdata->prepare();
    Judgementer->prepare();

    SongChannel->reset();
}
