//
// Created by admin on 2018/9/7.
//

#ifndef QT_BB_MANIAOBJECTS_H
#define QT_BB_MANIAOBJECTS_H

#include "maniaclass.h"
#include "Beatmap.h"
#include "ManiaRuleset.h"
#include "GameJudgement.h"
#include "defext.h"

namespace nso{

    class ManiaObject {
    public:
        //创建各种物件
        Interface(void addPlayingObjects(
                vector<JudgeableObject<ManiaPlaytimeData>*> *judge,
                          vector<PlayingHitObject*> *draw))
    };

    class ManiaNoteObject : public ManiaObject{
    public:
        ManiaNoteObject(HitCircle *rawObject, Beatmap *rawBeatmap);;

        void addPlayingObjects(vector<JudgeableObject<ManiaPlaytimeData> *> *judge, vector<PlayingHitObject *> *draw);

    private:
        HitCircle *RawObject;
        Beatmap *RawBeatmap;
    };

    class ManiaHoldObject : public ManiaObject{
    public:
        ManiaHoldObject(ManiaHold *rawObject,Beatmap *rawBeatmap);

        void addPlayingObjects(vector<JudgeableObject<ManiaPlaytimeData> *> *judge, vector<PlayingHitObject *> *draw);

    private:
        ManiaHold *RawObject;
        Beatmap *RawBeatmap;
    };

    class ManiaBaseJudgeObject : public JudgeableObject<ManiaPlaytimeData> {
    public:
        ManiaBaseJudgeObject();

        double getStartJudgeTime();
        double getEndJudgeTime();
        Interface(void onJudge(ManiaPlaytimeData *data)) //具体的判定逻辑
        Interface(void onRelease())
        Interface(void onTimeout(ManiaPlaytimeData *data))

        void release();

        void applyScore(ManiaPlaytimeData *data, int type, int score, double offset);
        bool isReleased(); //判断是否被释放
        int depth(); //物件判定顺序，主要是那些会消耗事件的需要给值

        GetSet(int,Line)
        GetSet(double,MaxJudgeTime)
        GetSet(int,JudgeResult)
    protected:
        Beatmap *RawBeatmap;
        double StartJudgeTime;
        double EndJudgeTime;
        double MaxJudgeTime;
        int Depth;
        int Line;
        int JudgeResult;
        bool Released;
    };

    class ManiaNoteJudgeObject : public ManiaBaseJudgeObject {
    public:
        ManiaNoteJudgeObject(PlayingNote *note, Beatmap *beatmap);

        void onJudge(ManiaPlaytimeData *data);

        void onRelease();
        void onTimeout(ManiaPlaytimeData *data);
    private:
        PlayingNote *Note;
    };

    class ManiaHoldStartJudgeObject : public ManiaBaseJudgeObject {
    public:
        ManiaHoldStartJudgeObject(PlayingHold *hold, Beatmap *beatmap);

        void onJudge(ManiaPlaytimeData *data);

        void onRelease(){ }
        void onTimeout(ManiaPlaytimeData *data);
    private:
        PlayingHold *Hold;
    };

    class ManiaHoldTickJudgeObject : public ManiaBaseJudgeObject {
    public:
        ManiaHoldTickJudgeObject(PlayingHold *hold,double offset, Beatmap *beatmap);

        void onJudge(ManiaPlaytimeData *data);

        void onRelease(){ }

        void onTimeout(ManiaPlaytimeData *data);
    private:
        PlayingHold *Hold;
        bool pressed;
    };


    class ManiaHoldEndJudgeObject : public ManiaBaseJudgeObject {
    public:
        ManiaHoldEndJudgeObject(PlayingHold *hold, ManiaHoldStartJudgeObject *start,
                                vector<ManiaHoldTickJudgeObject *> *ticks, Beatmap *beatmap);

        ~ManiaHoldEndJudgeObject();

        void onJudge(ManiaPlaytimeData *data);

        void onRelease();

        void onTimeout(ManiaPlaytimeData *data);
    private:
        PlayingHold *Hold;
        ManiaHoldStartJudgeObject *StartObject;
        vector<ManiaHoldTickJudgeObject*> *TickObjects;
        bool pressed;
    };

}




#endif //QT_BB_MANIAOBJECTS_H
