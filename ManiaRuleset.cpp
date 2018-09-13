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
    if (paused) {
        SongChannel->postStart(1000);
        paused = false;
    } else {
        SongChannel->postStart(2500);
    }
}

void ManiaGame::pauseGame() {
    SongChannel->pause();
    paused = true;
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

bool ManiaGame::running() {
    return SongChannel->isPlaying();
}

ManiaGame::ManiaGame(EdpFile *f, ManiaSetting *setting) : FrameTime(0), OsuFile(f), SetDirectory(
        new EdpFile(f->getParentPath())), Setting(setting), paused(false) {

}

ManiaGame::~ManiaGame() {
    delete Drawdata;
    delete Judgementer;
    ForEachLong(*Objects,itr,vector<ManiaObject*>::iterator) {
        ManiaObject *object = *itr;
        delete object;
    }
    delete Objects;
    delete Score;
    delete PlayingData;
    delete GameKeyFrame;
    delete OsuBeatmap;
    delete SetDirectory;
    SongChannel->release();
    delete SongChannel;
}

AutoKeyPipe::AutoKeyPipe() : time(0), minHoldTime(125) {

}

void AutoKeyPipe::load(Beatmap *beatmap, ManiaSetting *setting) {
    int key = beatmap->getKeys();
    vector<vector<HitObject *> *> listByX;
    vector<int> &keybinding = *((*setting->getKeyBinding())[key - 1]);
    ForI(i,0,key){
        listByX.push_back(new vector<HitObject *>());
    }
    ForEachLong(beatmap->hitobjects, itr, vector<HitObject *>::iterator) {
        HitObject *object = *itr;
        listByX[ManiaUtil::positionToLine(object->x, key)]->push_back(object);
    }

    ForI(i,0,key){
        vector<HitObject *> &divs = *(listByX[i]);
        ForEachLong(divs, itr, vector<HitObject *>::iterator) {
            HitObject *object = *itr;
            if ((object->type & HitObject::TYPE_MASK) == HitObject::TYPE_MANIA_HOLD) {
                int keynum = keybinding[i];
                events.push_back(KeyEvent{
                        KeyState::Down,
                        keynum,
                        "a",
                        (double)object->time
                });
                events.push_back(KeyEvent{
                        KeyState::Up,
                        keynum,
                        "a",
                        (double)(((ManiaHold &) *object).endTime)
                });
            } else {
                int keynum = keybinding[i];

                int nextObjectTime;
                vector<HitObject *>::iterator next = itr + 1;
                if (next != divs.end()) {
                    nextObjectTime = (*next)->time;
                } else {
                    nextObjectTime = 1000000000;
                }

                int offset;
                if (nextObjectTime - object->time > 180) {
                    offset = 90;
                } else {
                    offset = (nextObjectTime - object->time) / 2;
                    if (offset < 30) {
                        offset = 30;
                    }
                }

                events.push_back(KeyEvent{
                        KeyState::Down,
                        keynum,
                        "a",
                        (double)object->time
                });
                events.push_back(KeyEvent{
                        KeyState::Up,
                        keynum,
                        "a",
                        (double)(object->time + offset)
                });
            }
        }
    }
    sortByTime();
}

bool AutoKeyPipe::outputNext() {
    return events.size() > 0 && (--events.end())->rawtime < time;
}

void AutoKeyPipe::update(double t) {
    time = t;
}

ManiaSetting::~ManiaSetting() {
    vector<vector<int>*> tmpb;
    KeyBinding->swap(tmpb);
    ForEachLong(tmpb,it1,vector<vector<int>*>::iterator) {
        vector<int> tmp;
        (*it1)->swap(tmp);
    }
}


#define BindKey(keyn,...) int a##keyn[keyn] = {__VA_ARGS__};\
vector<int>* key##keyn = new vector<int>(a##keyn,a##keyn+keyn);\
KeyBinding->push_back(key##keyn);

ManiaSetting::ManiaSetting() {
    KeyBinding = new vector<vector<int>*>();
    BindKey(1,Qt::Key_Space)
    BindKey(2,Qt::Key_A,Qt::Key_S)
    BindKey(3,Qt::Key_A,Qt::Key_S,Qt::Key_D)
    BindKey(4,Qt::Key_A,Qt::Key_S,Qt::Key_K,Qt::Key_L)
    BindKey(5,Qt::Key_A,Qt::Key_S,Qt::Key_Space,Qt::Key_K,Qt::Key_L)
    BindKey(6,Qt::Key_A,Qt::Key_S,Qt::Key_D,Qt::Key_J,Qt::Key_K,Qt::Key_L)
    BindKey(7,Qt::Key_A,Qt::Key_S,Qt::Key_D,Qt::Key_Space,Qt::Key_J,Qt::Key_K,Qt::Key_L)
    BindKey(8,Qt::Key_A,Qt::Key_S,Qt::Key_D,Qt::Key_J,Qt::Key_K,Qt::Key_L)
}

int ManiaUtil::positionToLine(double pos, int key) {
    if (key == 8) {
        return 1 + (int) (pos / (512.0 / 7));
    } else {
        return (int)(pos / (512.0 / key));
    }
}

int ManiaUtil::positionToLine(PlayingHitObject *obj, Beatmap *bmp) {
    return positionToLine(obj->getX(), (int) (bmp->CircleSize + 0.001));
}

double ManiaUtil::hitWindow(double od, int score) {
    if (score == Mania::S300k) {
        return Mania::HitWindow300k;
    } else {
        double s = od / 10.0;
        return Mania::HitWindowScale[score]
               * (Mania::HitWindowMax * (1 - s) + Mania::HitWindowMin * s);
    }
}

int ManiaUtil::hitWindowFor(double od, double offset) {
    if (offset < 0) {
        offset = -offset;
    }
    if (offset < hitWindow(od, Mania::S300k)) {
        return Mania::S300k;
    } else if (offset < hitWindow(od, Mania::S300)){
        return Mania::S300;
    } else if (offset < hitWindow(od, Mania::S200)){
        return Mania::S200;
    } else if (offset < hitWindow(od, Mania::S100)){
        return Mania::S100;
    } else if (offset < hitWindow(od, Mania::S50)){
        return Mania::S50;
    } else {
        return Mania::S_MISS;
    }
}

void ManiaScore::applyScore(ManiaHitResult &result) { //apply 一个成绩
    RecentScore = result.score;

    switch (result.type) {
        case Mania::ScoreType_Note:{
            TotalScore += Mania::BaseScore[result.score];
            CurrentBonusRate += Mania::BonusMul[result.score];
            CurrentBonusRate = Clamp(0, CurrentBonusRate, 100);
            TotalBonus += (int)(Mania::BaseBonus[result.score] * sqrt(CurrentBonusRate)+0.0001);
        }break;

        case Mania::ScoreType_Tick:
        default:{
            //tick不影响分数
        }break;
    }


    if (result.score != Mania::S_MISS) {
        Combo++;
    } else {
        if (MaxCombo < Combo) {
            MaxCombo = Combo;
        }
        Combo = 0;
    }
}

int ManiaScore::getScore() {
    int value = TotalBonus + TotalScore;
    //return value;
    if (value == 640 * TotalHit) {
        //满分检测
        return Mania::Max_Score;
    } else {
        return static_cast<int>((Mania::Max_Score * (int64)value) / (640 * TotalHit));
    }
}

ManiaScore::ManiaScore(Beatmap *beatmap) :
        RawBeatmap(beatmap),
        RecentScore(0),
        TotalScore(0),
        TotalBonus(0),
        CurrentBonusRate(100),
        MaxCombo(0),
        Combo(0) {
    TotalHit = 0;
    ForEachLong(beatmap->hitobjects, itr, vector<HitObject *>::iterator) {
        HitObject *object = *itr;
        TotalHit += (object->type & HitObject::TYPE_MASK) == HitObject::TYPE_MANIA_HOLD ? 2 : 1;
    }
}

void GameHolder::loadGame(string &path) {
    EdpFile f(path);
    loadGame(&f);
}

void GameHolder::loadGame(EdpFile *osuFile) {
    if (checkGame()) {
        DebugI("forget to release game ???")
        releaseGame();
    }
    if (Setting == NULL) {
        Setting = new ManiaSetting();
    }
    Game = new ManiaGame(osuFile,Setting);
    Game->prepareGame();
    savedPath = osuFile->getFullPath();
    Game->getSongChannel()->setVolume(BaseVolume);
    if (modIsEnable(Mania::MOD_AUTO)) {
        AutoPlay = new AutoKeyPipe();
        AutoPlay->load(Game->getOsuBeatmap(), Game->getSetting());
        Game->linkKeyInput(AutoPlay);
    } else {
        KeyPipe = new QTKeyPipe();
        KeyPipe->setTimer(Game->getSongChannel());
        Game->linkKeyInput(KeyPipe);
    }
}

void GameHolder::reloadGame() {
    if (checkGame()) {
        releaseGame();
        loadGame(savedPath);
    }
}
