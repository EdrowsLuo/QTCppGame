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

void ManiaPlaytimeData::setTimer(EdpTimer *t) {
    timer = t;
}


ManiaDrawdata::ManiaDrawdata(nso::Beatmap &beatmap) :
        Preempt(500),
        LineCount((int) (beatmap.CircleSize + 0.01)), SpeedChange(false) {
    beats.insert(beats.begin(), beatmap.controlPoints.Beats.begin(), beatmap.controlPoints.Beats.end());
    float currentPosition = beatmap.controlPoints.Timings.begin()->Time - 5000;
    double currentTime = beatmap.controlPoints.Timings.begin()->Time - 5000;
    double speed = 1;
    ForEachLong(beatmap.controlPoints.Timings, itr, vector<TimingControlPoint>::iterator) {
        ScrollingControlPoint point;
        point.speed = static_cast<float>(itr->SpeedMultiplier);
        point.startTime = itr->Time;
        point.startPosition = static_cast<float>((point.startTime - currentTime) * speed + currentPosition);
        speed = point.speed;
        currentPosition = point.startPosition;
        currentTime = point.startTime;
        scrollingPoints.push_back(point);
    }
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

    if (SpeedChange) {
        ForEachLong(rawObjects, itr, vector<PlayingHitObject *>::iterator) {
            PlayingHitObject *object = *itr;
            ScrollingObject *scrollingObject = new ScrollingObject;
            scrollingObject->startPosition = timeToPosition(object->getTime());
            scrollingObject->endPosition = timeToPosition(object->getEndTime());
            scrollingObject->type =
                    (object->getType() == HitObject::TYPE_MANIA_HOLD) ? 0 //ManiaDrawdata::HOLD
                                                                      : 1; // ManiaDrawdata::NOTE;
            scrollingObject->line = ManiaUtil::positionToLine(object->getX(), LineCount);
            scrollingObject->rawObject = object;
            DebugI(scrollingObject->startPosition << "  :  " << scrollingObject->endPosition)
            srawObjects.push_back(scrollingObject);
        }
        sobjectsToAdd.clear();
        sobjectsToAdd.insert(sobjectsToAdd.end(), srawObjects.begin(), srawObjects.end());
        sobjectsUsing.clear();
    }
}

void ManiaDrawdata::update(double time) {

    if (SpeedChange) {
        updateTypeSpeedChange(time);
        return;
    }


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
        ManiaDrawdataNode drawdata;
        if (object->getType() == HitObject::TYPE_MANIA_HOLD) {
            float t = (object->getTime() - (float) time) / Preempt;
            t = Clamp(0, t, 1);
            float t2 = (object->getEndTime() - (float) time) / Preempt;
            t2 = Clamp(0, t2, 1);
            drawdata.rawObject = object;
            drawdata.type = ManiaDrawdata::HOLD;
            drawdata.line = ManiaUtil::positionToLine(object->getX(), LineCount);
            drawdata.position = t;
            drawdata.endposition = t2;
        } else {
            float t = (object->getTime() - (float) time) / Preempt;
            t = Clamp(0, t, 1);
            drawdata.rawObject = object;
            drawdata.type = ManiaDrawdata::NOTE;
            drawdata.line = ManiaUtil::positionToLine(object->getX(), LineCount);
            drawdata.position = t;
            drawdata.endposition = t;
        }
        datas.push_back(drawdata);
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

void ManiaDrawdata::updateTypeSpeedChange(double time) {
    /*//DebugI("time: " << time)
    time = timeToPosition(time);
    //DebugI("pos : " << time)
    //添加
    double preShowTime = time + Preempt;
    while (!sobjectsToAdd.empty()) {
        ScrollingObject *object = sobjectsToAdd.front();
        if (object->startPosition <= preShowTime) {
            //onShowObject(object);
            sobjectsUsing.push_back(object);
            sobjectsToAdd.pop_front();
        } else {
            break;
        }
    }

    //舍弃不需要了的物件
    ForEachLong(sobjectsUsing, it, vector<ScrollingObject*>::iterator) {
        if ((*it)->rawObject->isReleased()) {
            //onHideObject(object);
            it = sobjectsUsing.erase(it);
            it--;
        } else if ((*it)->endPosition < time) {
            (*it)->rawObject->release();
            //onHideObject(object);
            it = sobjectsUsing.erase(it);
            it--;
        }
    }

    //开始组织数据
    datas.clear();
    ForEachLong(sobjectsUsing, it, vector<ScrollingObject*>::iterator) {
        //if (it->type == ManiaDrawdata::HOLD) {
            float t = static_cast<float>(((*it)->startPosition - time) / Preempt);
            t = Clamp(0, t, 1);
            float t2 = static_cast<float>(((*it)->endPosition - time) / Preempt);
            t2 = Clamp(0, t2, 1);
            datas.push_back(ManiaDrawdataNode{
                    (*it)->rawObject,
                    (*it)->type,
                    (*it)->line,
                    t,
                    t2
            });
       *//* } else {
            float t = static_cast<float>((it->startPosition - time) / Preempt);
            t = Clamp(0, t, 1);
            datas.push_back(ManiaDrawdataNode{
                    it->rawObject,
                    ManiaDrawdata::NOTE,
                    it->line,
                    t,
                    t
            });
        }*//*
    }

    beatsAvalible.clear();
    while ((!beats.empty()) && beats.front() < time) {
        beats.pop_front();
    }
    ForEachLong(beats,itr,list<double>::iterator) {
        if (*itr < time + Preempt) {
            beatsAvalible.push_back((timeToPosition(*itr) - time) / Preempt);
        } else {
            break;
        }
    }*/
}

vector<ManiaDrawdataNode> &ManiaDrawdata::getDatas() {
    return datas;
}

vector<PlayingHitObject *> *ManiaDrawdata::rawObjectsPointer() {
    return &rawObjects;
}

vector<double> *ManiaDrawdata::getBeatsAvalibe() {
    return &beatsAvalible;
}

ScrollingControlPoint &ManiaDrawdata::findScrollingPoint(double time) {
    vector<ScrollingControlPoint>::iterator itr = scrollingPoints.begin();
    if (itr->startTime >= time) {
        return *itr;
    } else {
        itr++;
        while (itr != scrollingPoints.end()) {
            if (itr->startTime > time) {
                return *(itr - 1);
            }
            itr++;
        }
        return *(itr - 1);
    }
}

float ManiaDrawdata::timeToPosition(double time) {
    ScrollingControlPoint &sp = findScrollingPoint(time);
    return static_cast<float>(sp.startPosition + (time - sp.startTime) * sp.speed);
}

PlayingHitObject::PlayingHitObject(HitObject &h) :
        released(false),
        X(h.x),
        Y(h.y),
        Time(h.time),
        Type(h.type & HitObject::TYPE_MASK),
        HitSound(h.hitSound) {

}

bool PlayingHitObject::isReleased() {
    return released;
}

void PlayingHitObject::release() {
    released = true;
}


void ManiaGame::prepareGame() {
    BeatmapDecoder decoder(*OsuFile);
    OsuBeatmap = new Beatmap;
    try {
        decoder.parse(*OsuBeatmap);
        EdpFile songFile(*SetDirectory, OsuBeatmap->AudioFilename);
        Length = OsuBeatmap->avalibleLength() + 2000;
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
        DebugI(e.what())
    } catch (ioexception &e) {
        DebugI(e.what())
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

ManiaGame::ManiaGame(EdpFile *f, ManiaSetting *setting) :
         OsuFile(new EdpFile(f->getFullPath())), SetDirectory(
        new EdpFile(f->getParentPath())), Setting(setting),FrameTime(0), paused(false), Length(0) {

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

AutoKeyPipe::AutoKeyPipe() : minHoldTime(125), time(0) {

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
                KeyEvent event;
                event.type = KeyState::Down;
                event.key = keynum;
                event.text = "a";
                event.rawtime = (double)object->time;
                events.push_back(event);
                event.type = KeyState::Up;
                event.rawtime = (double)(((ManiaHold &) *object).endTime);
                events.push_back(event);
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

                KeyEvent event;
                event.type = KeyState::Down;
                event.key = keynum;
                event.text = "a";
                event.rawtime = (double)object->time;
                events.push_back(event);
                event.type = KeyState::Up;
                event.rawtime = (double)(object->time + offset);
                events.push_back(event);
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
        Offset(0),
        TotalHit(0),
        RawBeatmap(beatmap),
        RecentScore(0),
        TotalScore(0),
        TotalBonus(0),
        CurrentBonusRate(100),
        MaxCombo(0),
        Combo(0),
        HitCount(0),
        AccScore(0),
        PassedCombo(0),
        HitCounter(new int[6]){
    HitCounter[0] = 0;
    HitCounter[1] = 0;
    HitCounter[2] = 0;
    HitCounter[3] = 0;
    HitCounter[4] = 0;
    HitCounter[5] = 0;
    TotalHit = 0;
    ForEachLong(beatmap->hitobjects, itr, vector<HitObject *>::iterator) {
        HitObject *object = *itr;
        TotalHit += (object->type & HitObject::TYPE_MASK) == HitObject::TYPE_MANIA_HOLD ? 2 : 1;
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

            AccScore += Mania::BaseAcc[result.score];
            HitCount++;

            HitCounter[result.score]++;
        }break;

        case Mania::ScoreType_Tick:
        default:{
            //tick不影响分数
            if (result.score == Mania::S_MISS) {
                CurrentBonusRate = 0;
            }
        }break;
    }

    PassedCombo++;
    if (result.score > Mania::S_MISS) {
        Combo++;
    } else {
        Combo = 0;
    }
    if (MaxCombo < Combo) {
        MaxCombo = Combo;
    }
}

double ManiaScore::getAccuracy() {
    if (HitCount == 0) {
        return 1;
    } else {
        return AccScore / (HitCount * 300.0);
    }
}

string ManiaScore::getRanking() {
    if (AccScore == HitCount * 300) {
        return Mania::Ranking_SS;
    } else {
        double acc = getAccuracy();
        if (acc >= 0.95) {
            return Mania::Ranking_S;
        } else if (acc >= 0.90) {
            return Mania::Ranking_A;
        } else if (acc >= 0.80) {
            return Mania::Ranking_B;
        } else if (acc >= 0.70) {
            return Mania::Ranking_C;
        } else {
            return Mania::Ranking_D;
        }
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
    DebugI("load game : " << osuFile->getFullPath())
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

GameHolder::GameHolder() :
        EscPressed(false),
        Mods(0),
        BaseVolume(0.4f),
        Game(NULL),
        Channel(NULL),
        Setting(NULL),
        KeyPipe(NULL),
        AutoPlay(NULL),
        SpeedLevel(10),
        EnableBackground(true) {

}

bool GameHolder::modIsEnable(int mod) {
    return (Mods & mod) == mod;
}

bool GameHolder::enableMod(int mod) {
    if (checkGame()) {
        DebugI("you can't change mod when game is loaded!")
        return false;
    }
    Mods |= mod;
    return true;
}

bool GameHolder::disableMod(int mod) {
    if (checkGame()) {
        DebugI("you can't change mod when game is loaded!")
        return false;
    }
    Mods &= ~mod;
    return true;
}

bool GameHolder::loadMusic(const string &path, int previewTime) {
    if (checkGame()) {
        DebugI("you can't change music when game is loaded!")
        return false;
    }
    if (Channel != NULL) {
        Channel->release();
        delete Channel;
        Channel = NULL;
    }
    Channel = new EdpBassChannel(path);
    Channel->setVolume(BaseVolume);
    Channel->seekTo(previewTime);
    Channel->play();
    return true;
}

void GameHolder::pauseNormalMusic() {
    if (Channel != NULL) {
        Channel->pause();
    }
}

void GameHolder::playNormalMusic() {
    if (Channel != NULL) {
        Channel->reset();
        Channel->play();
    }
}

bool GameHolder::checkGame() {
    return Game != NULL;
}

void GameHolder::startGame() {
    if (checkGame()) {
        if (!Game->getSongChannel()->isPlaying()) {
            Game->getSongChannel()->setVolume(BaseVolume);
            Game->runGame();
            if (Channel != NULL) {
                Channel->pause();
            }
        }
    }
}

void GameHolder::releaseGame() {
    if (checkGame()) {
        Game->pauseGame();
        if (modIsEnable(Mania::MOD_AUTO)) {
            delete AutoPlay;
            AutoPlay = NULL;
        } else {
            delete KeyPipe;
            KeyPipe = NULL;
        }
        delete Game;
        Game = NULL;
    }
}

void GameHolder::update() {
    if (checkGame()) {
        if (Game->updateTime()) {
            if (modIsEnable(Mania::MOD_AUTO)) {
                AutoPlay->update(Game->getFrameTime());
            }
            Game->update();
        }
    }

}

void GameHolder::endUpdate() {
    EscPressed = false;
}

void GameHolder::mkeyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Tab) {
        if (checkGame()) {
            Game->getSongChannel()->seekTo(Game->getSongChannel()->getTime() + 1000);
        }
    }


    if (event->isAutoRepeat()) {
        return;
    }

    if (event->key() == Qt::Key_Escape) {
        EscPressed = true;
    }

    if (KeyPipe != NULL) {
        KeyPipe->keyPressEvent(event);
    }
}

void GameHolder::mkeyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        return;
    }
    if (KeyPipe != NULL) {
        KeyPipe->keyReleaseEvent(event);
    }
}

void GameHolder::setBaseVolume(float v) {
    v = Clamp(0, v, 1);
    BaseVolume = v;
    if (Game != NULL) {
        Game->getSongChannel()->setVolume(BaseVolume);
    }
    if (Channel != NULL) {
        Channel->setVolume(BaseVolume);
    }
}
