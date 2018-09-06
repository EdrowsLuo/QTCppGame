//
// Created by admin on 2018/9/6.
//

#ifndef QT_BB_RULESETMANIA_H
#define QT_BB_RULESETMANIA_H

#include "GameJudgement.h"
#include "KeyIO.h"
#include "defext.h"

namespace nso{

    class ManiaRuleset;

    class ManiaPlaytimeData;

    class MainaPlaytimeData:public JudgeData{
    public:
        double getFrameTime();
        EdpTimer *getTimer();
        void update();
        void endJudge();

        Getter(vector<KeyHolder*> &,Keys)
        GetSetO(KeyFrame,MKeyFrame)

    protected:
        EdpTimer *timer;
        double frameTime;

        vector<KeyHolder*> Keys;
        KeyFrame *MKeyFrame;
    };


    class ManiaRuleset {

    };
}


#endif //QT_BB_RULESETMANIA_H
