//
// Created by admin on 2018/9/6.
//

#ifndef QT_BB_GAMEJUDGEMENT_H
#define QT_BB_GAMEJUDGEMENT_H

#include "defext.h"
#include "EdpTimer.h"
#include "Edp.h"
#include <vector>

using namespace edp;
using namespace std;

namespace nso{

    class JudgeData;
    template <typename _Data> class JudgeableObject;
    template <typename _Data> class GameJudgement;

    class JudgeData:public ILinkTimer,public IUpdate{
    public:
        Interface(void update())
        Interface(void endJudge())
        Interface(double getFrameTime())
        Interface(EdpTimer *getTimer())
    };

    template <typename _Data>
    class JudgeableObject{
    public:
        Interface(double getStartJudgeTime())
        Interface(double getEndJudgeTime())
        Interface(void onJudge(_Data &data)) //具体的判定逻辑
        Interface(void release()) //超时被释放
        Interface(bool isReleased()) //判断是否被释放
        Interface(unsigned int depth()) //物件判定顺序
    };

    template <typename _Data>
    class GameJudgement : public IUpdate {
    public:

        explicit GameJudgement(_Data *d);

        void prepare();

        virtual void onUpdate() {}
        virtual void onFinishUpdate() {}
        void update();

    protected:

        void updateUsingObjects(double time);
        virtual void doJudgement(double time);
        void relaseObjects(double time);

    private:
        _Data *data;
        //原始物件
        vector<JudgeableObject<_Data>*> judgeObjects;
        //还没有被添加的物件
        list<JudgeableObject<_Data>*> judgeObjectsToAdd;
        //正在判定中的物件
        vector<JudgeableObject<_Data>*> judgeObjectsUsing;
    };
}



#endif //QT_BB_GAMEJUDGEMENT_H
