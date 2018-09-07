//
// Created by admin on 2018/9/6.
//

#ifndef QT_BB_RULESETMANIA_H
#define QT_BB_RULESETMANIA_H

#include "GameJudgement.h"
#include "KeyIO.h"
#include "defext.h"
#include "Beatmap.h"

namespace nso{

    class ManiaRuleset;

    class ManiaPlaytimeData;

    class ManiaDrawdata;

    class PlayingHitObject;

    class PlayingNote;

    class PlayingHold;

    class ManiaUtil;

    class ManiaGameSetting;

    class ManiaGame;

    struct ManiaDrawdataNode;

    class ManiaPlaytimeData:public JudgeData{
    public:
        double getFrameTime();
        EdpTimer *getTimer();
        void update();
        void endJudge();

        Getter(vector<KeyHolder*> &,Keys)
        GetSetO(KeyFrame,MKeyFrame)

        void setTimer(EdpTimer *t){
            timer = t;
        }

    protected:
        EdpTimer *timer;
        double frameTime;

        vector<KeyHolder*> Keys;
        KeyFrame *MKeyFrame;
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

        void prepare();
        void update(double time);

        vector<ManiaDrawdataNode>& getDatas(){
            return datas;
        }

        GetSet(int ,LineCount)

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
    };

    class ManiaSetting{

#define BindKey(keyn,...) vector<int>* key##keyn = new vector<int>{__VA_ARGS__};\
KeyBinding->push_back(key##keyn);

    public:
        static ManiaSetting* DefaultSetting;


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
            ForEachLong(tmpb,it1,vector<vector<int>*>::iterator){
                vector<int> tmp;
                (*it1)->swap(tmp);
            }}
        }
    private:
        vector<vector<int>*>* KeyBinding;
    };

    class ManiaGame{
    public:
        explicit ManiaGame(EdpFile *f,ManiaSetting *setting = ManiaSetting::DefaultSetting):OsuFile(f),Setting(setting) {

        }

        //加载Beatmap，构建输入输出模块的连接
        void prepareGame() {

        }

    protected:
        EdpFile *OsuFile;
        ManiaSetting *Setting;


    };

    class ManiaRuleset {

    };
}


#endif //QT_BB_RULESETMANIA_H
