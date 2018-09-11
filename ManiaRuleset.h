//
// Created by admin on 2018/9/6.
//

#ifndef QT_BB_RULESETMANIA_H
#define QT_BB_RULESETMANIA_H

#include <cmath>
#include "KeyIO.h"
#include "defext.h"
#include "EdpBass.h"
#include "Beatmap.h"
#include "maniaclass.h"
#include "ManiaObjects.h"
#include "GameJudgement.h"
#include "types.h"


using namespace edp;

namespace nso{

    class ManiaPlaytimeData:public JudgeData,public IUpdateByTime{
    public:

        EdpTimer *getTimer();
        void update(double time);

        double getFrameTime();
        void startJudge();
        void endJudge();

        Getter(vector<KeyHolder*> &,Keys)
        GetSetO(ManiaScore,Score)
        GetSetO(KeyFrame,MKeyFrame)

        void setTimer(EdpTimer *t){
            timer = t;
        }

    protected:
        EdpTimer *timer;
        double frameTime;

        vector<KeyHolder*> Keys;
        KeyFrame *MKeyFrame;

        ManiaScore *Score;
    };

    namespace Mania {
        static const int Max_Score = 1000000;

        static const int ScoreType_Note = 1, ScoreType_Tick = 2;
        //基础分数比例以及enum
        static const int S300k = 5, S300 = 4, S200 = 3, S100 = 2, S50 = 1, S_MISS = 0;
        static const int BaseScore[6] = {0, 50, 100, 200, 300, 320};
        //额外基础分
        static const int BaseBonus[6] = {0, 4, 8, 16, 32, 32};
        //倍率分，负值为惩罚
        static const int BonusMul[6] = {-100, -44, -24, -8, 1, 2};

        static const double HitWindowMax = 80 , HitWindowMin = 34.5 , HitWindow300k = 20;

        static const double HitWindowScale[6] = {2.5, 2.1, 1.8, 1.3, 1, 1};

        static const int MOD_AUTO = 1, MODE_NONE = 0;
    };


    struct ManiaHitResult{
        int type;
        int score;
        double offset;
    };


    class ManiaScore {
    public:

        ManiaScore(Beatmap *beatmap) :
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

        int getScore() {
            int value = TotalBonus + TotalScore;
            //return value;
            if (value == 640 * TotalHit) {
                //满分检测
                return Mania::Max_Score;
            } else {
                return static_cast<int>((Mania::Max_Score * (int64)value) / (640 * TotalHit));
            }
        }

        void applyScore(ManiaHitResult &result) { //apply 一个成绩
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

    public:
        Beatmap *RawBeatmap;
        int Offset;
        int RecentScore;
        int TotalScore;
        int TotalBonus;
        int CurrentBonusRate;
        int TotalHit;
        int MaxCombo;
        int Combo;
    };

    class PlayingHitObject{
    protected:
        explicit PlayingHitObject(HitObject &h);

    public:
        VGetter(int,X)
        VGetter(int,Y)
        VGetter(int,Time)
        VaGetter(int,EndTime){ return Time; }
        VaGetter(int,FinalTime){ return getEndTime(); } //超时时间
        VGetter(int,Type)
        VGetter(int,HitSound)
        bool isReleased(){
            return released;
        }

        virtual void release(){
            released = true;
        }
    protected:
        bool released;
        int X;
        int Y;
        int Time;
        int Type;
        int HitSound;
    };

    class PlayingNote:public PlayingHitObject{
    public:
        explicit PlayingNote(HitCircle &hitObject):PlayingHitObject(hitObject){ }
    };

    class PlayingHold:public PlayingHitObject{
    public:
        explicit PlayingHold(ManiaHold &object) : PlayingHitObject(object), EndTime(object.endTime) { }

        OverrideGetter(int ,EndTime){ return EndTime; }

    private:
        int EndTime;
    };

    struct ManiaDrawdataNode{
        PlayingHitObject *rawObject;
        int type;
        int line;
        float position;
        float endposition;
    };

    class ManiaDrawdata{
    public:
        static const int NOTE = 0;
        static const int HOLD = 1;

        explicit ManiaDrawdata(Beatmap &beatmap);
        ManiaDrawdata();

        void prepare();
        void update(double time);

        vector<ManiaDrawdataNode>& getDatas(){
            return datas;
        }

        vector<PlayingHitObject*> * rawObjectsPointer(){
            return &rawObjects;
        }

        vector<double> *getBeatsAvalibe(){
            return &beatsAvalible;
        }

        GetSet(int ,LineCount)
        GetSet(float,Preempt)

    protected:
        virtual void onShowObject(PlayingHitObject *object){};
        virtual void onHideObject(PlayingHitObject *object){};

    protected:
        float Preempt;
        int LineCount;

        vector<ManiaDrawdataNode> datas;

        //原始物件
        vector<PlayingHitObject*> rawObjects;
        //还没有被添加的物件
        list<PlayingHitObject*> objectsToAdd;
        //正在判定中的物件
        vector<PlayingHitObject*> objectsUsing;

        vector<double> beatsAvalible;

        list<double> beats;
    };

    class ManiaUtil{
    public:
        static int positionToLine(double pos, int key){
            if (key == 8) {
                return 1 + (int) (pos / (512.0 / 7));
            } else {
                return (int)(pos / (512.0 / key));
            }
        }

        static int positionToLine(PlayingHitObject *obj, Beatmap *bmp) {
            return positionToLine(obj->getX(), (int) (bmp->CircleSize + 0.001));
        }

        static double hitWindow(double od,int score) {
            if (score == Mania::S300k) {
                return Mania::HitWindow300k;
            } else {
                double s = od / 10.0;
                return Mania::HitWindowScale[score]
                       * (Mania::HitWindowMax * (1 - s) + Mania::HitWindowMin * s);
            }
        }

        static int hitWindowFor(double od, double offset) {
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
    };

    class ManiaSetting{

#define BindKey(keyn,...) int a##keyn[keyn] = {__VA_ARGS__};\
vector<int>* key##keyn = new vector<int>(a##keyn,a##keyn+keyn);\
KeyBinding->push_back(key##keyn);

    public:
        static ManiaSetting& DefaultSetting;

        ManiaSetting(){
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

        ~ManiaSetting(){
            vector<vector<int>*> tmpb;
            KeyBinding->swap(tmpb);
            ForEachLong(tmpb,it1,vector<vector<int>*>::iterator) {
                vector<int> tmp;
                (*it1)->swap(tmp);
            }
        }

        Getter(vector<vector<int>*>*,KeyBinding)
    private:
        vector<vector<int>*>* KeyBinding;
    };

    class ManiaGame{
    public:
        explicit ManiaGame(EdpFile *f, ManiaSetting *setting) : FrameTime(0), OsuFile(f), SetDirectory(
                new EdpFile(f->getParentPath())), Setting(setting) {

        }

        virtual bool running(){
            return SongChannel->isPlaying();
        }

        virtual void reset();

        //开始游戏
        virtual void runGame();

        //暂停游戏
        virtual void pauseGame();

        //结束游戏
        virtual void stopGame();

        virtual bool updateTime();
        //循环更新
        virtual void update();

        //一次循环结束
        virtual void endUpdate();

        //加载Beatmap，构建输入输出模块的连接
        virtual void prepareGame();

        //连接按键输入
        virtual void linkKeyInput(KeyInput *in);

        Getter(EdpBassChannel *,SongChannel)
        Getter(ManiaDrawdata *,Drawdata)
        Getter(ManiaPlaytimeData *,PlayingData)
        Getter(Beatmap *,OsuBeatmap)
        Getter(ManiaSetting *,Setting)
        Getter(double,FrameTime)

    protected:
        EdpFile *OsuFile;
        EdpFile *SetDirectory;
        ManiaSetting *Setting;

        Beatmap *OsuBeatmap;
        EdpBassChannel *SongChannel;
        KeyFrame *GameKeyFrame;

        double FrameTime;

        ManiaPlaytimeData *PlayingData;

        vector<ManiaObject*> *Objects;

        ManiaScore *Score;

        GameJudgement<ManiaPlaytimeData> *Judgementer;
        ManiaDrawdata *Drawdata;

    };

    class AutoKeyPipe:public QueryKeyInput,public IUpdateByTime{
    public:

        double minHoldTime;

        AutoKeyPipe() : time(0), minHoldTime(125) {

        }

       /* virtual void start() {
            output = true;
            if (outputNext()) {
                DebugI("start")
            }
        }

        virtual void end() {
            output = false;
            if (outputNext()) {
                DebugI("end")
            }
        }

        bool getKeyEvevnt(KeyEvent &event) {
            if (outputNext()) {
                event = events.back();
                events.erase(events.end() - 1);
                Debug("read one input event");
                DebugI("key: " << event.key << " time: " << event.rawtime << " type: " << event.type << " st: " << time)
                return true;
            } else {
                return false;
            }
        }*/

        void load(Beatmap *beatmap, ManiaSetting *setting) {
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

            /*ForEachLong(beatmap->hitobjects, itr, vector<HitObject *>::iterator) {
                HitObject *object = *itr;
                if ((object->type & HitObject::TYPE_MASK) == HitObject::TYPE_MANIA_HOLD) {
                    int keynum = keybinding[ManiaUtil::positionToLine(object->x, key)];
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
                    int keynum = keybinding[ManiaUtil::positionToLine(object->x, key)];
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
                            (double)object->time + minHoldTime
                    });
                }
            }*/
            sortByTime();
            /*DebugI(keybinding[2])
            DebugI(keybinding[3])
            ForEachLong(events,i,vector<KeyEvent>::iterator) {
                KeyEvent &event = *i;
                DebugI("key: " << event.key << " time: " << event.rawtime << " type: " << event.type);
            }*/
        }

        virtual bool outputNext() {
            return events.size() > 0 && (--events.end())->rawtime < time;
        }

        void update(double t) {
            time = t;
        }

    private:
        double time;
    };



    /*
     * 长期存在，管理ManiaGame生命周期的类
     */
    class GameHolder{
    public:
        GameHolder() :
                Mods(0),
                BaseVolume(50){

        }

        bool modIsEnable(int mod) {
            return (Mods & mod) == mod;
        }

        void enableMod(int mod) {
            Mods |= mod;
        }

        void disableMod(int mod) {
            Mods &= ~mod;
        }

        void loadMusic(const string &path) {

        }

        void loadGame(EdpFile *osuFile) {
            Game = new ManiaGame(osuFile,new ManiaSetting());
            Game->prepareGame();
            //Game->getSongChannel()->setVolume(BaseVolume);
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

        void update(){
            if (Game->updateTime()) {
                if (modIsEnable(Mania::MOD_AUTO)) {
                    AutoPlay->update(Game->getFrameTime());
                }
                Game->update();
            }
        }

        virtual void mkeyPressEvent(QKeyEvent *event) {
            if (event->isAutoRepeat()) {
                return;
            }

            if (KeyPipe != NULL) {
                KeyPipe->keyPressEvent(event);
            }
        }

        virtual void mkeyReleaseEvent(QKeyEvent *event) {
            if (event->isAutoRepeat()) {
                return;
            }
            if (KeyPipe != NULL) {
                KeyPipe->keyReleaseEvent(event);
            }
        }

        Getter(ManiaGame *,Game)

    private:
        EdpBassChannel *Channel;
        float BaseVolume;

        QTKeyPipe *KeyPipe;
        AutoKeyPipe *AutoPlay;

        ManiaGame *Game;

        int Mods;
    };



    class ManiaRuleset {

    };
}


#endif //QT_BB_RULESETMANIA_H
