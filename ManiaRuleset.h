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

        ManiaScore(Beatmap *beatmap);

        int getScore();
        void applyScore(ManiaHitResult &result);

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
        static int positionToLine(double pos, int key);

        static int positionToLine(PlayingHitObject *obj, Beatmap *bmp);

        static double hitWindow(double od,int score);

        static int hitWindowFor(double od, double offset);
    };

    class ManiaSetting{
    public:
        static ManiaSetting& DefaultSetting;

        ManiaSetting();
        ~ManiaSetting();

        Getter(vector<vector<int>*>*,KeyBinding)
    private:
        vector<vector<int>*>* KeyBinding;
    };

    class ManiaGame{
    public:
        explicit ManiaGame(EdpFile *f, ManiaSetting *setting);
        ~ManiaGame();

        virtual bool running();

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

        AutoKeyPipe();

        void load(Beatmap *beatmap, ManiaSetting *setting);

        virtual bool outputNext();

        void update(double t);

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
                BaseVolume(0.5f),
                Game(NULL),
                Setting(NULL),
                KeyPipe(NULL),
                AutoPlay(NULL){

        }

        bool modIsEnable(int mod) {
            return (Mods & mod) == mod;
        }

        bool enableMod(int mod) {
            if (checkGame()) {
                DebugI("you can't change mod when game is loaded!")
                return false;
            }
            Mods |= mod;
            return true;
        }

        bool disableMod(int mod) {
            if (checkGame()) {
                DebugI("you can't change mod when game is loaded!")
                return false;
            }
            Mods &= ~mod;
            return true;
        }

        bool loadMusic(const string &path, int previewTime) {
            if (!checkGame()) {
                DebugI("you can't change music when game is loaded!")
                return false;
            }
        }

        bool checkGame() {
            return Game != NULL;
        }

        void loadGame(EdpFile *osuFile) {
            if (checkGame()) {
                DebugI("forget to release game ???")
                releaseGame();
            }
            if (Setting == NULL) {
                Setting = new ManiaSetting();
            }
            Game = new ManiaGame(osuFile,Setting);
            Game->prepareGame();
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

        //重载游戏，在retry时使用
        void reloadGame() {

        }

        //游戏结束释放游戏资源
        void releaseGame(){
            if (checkGame()) {
                if (modIsEnable(Mania::MOD_AUTO)) {
                    delete AutoPlay;
                    AutoPlay = NULL;
                } else {
                    delete KeyPipe;
                    KeyPipe = NULL;
                }
                delete Game;
            }
        }

        void update(){
            if (checkGame()) {
                if (Game->updateTime()) {
                    if (modIsEnable(Mania::MOD_AUTO)) {
                        AutoPlay->update(Game->getFrameTime());
                    }
                    Game->update();
                }
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

        ManiaSetting *Setting;

        ManiaGame *Game;

        int Mods;
    };



    class ManiaRuleset {

    };
}


#endif //QT_BB_RULESETMANIA_H
