//
// Created by admin on 2018/9/6.
//

#ifndef QT_BB_GAMEJUDGEMENT_H
#define QT_BB_GAMEJUDGEMENT_H

#include "defext.h"
#include "EdpTimer.h"
#include "Edp.h"
#include <vector>
#include <algorithm>

using namespace edp;
using namespace std;

namespace nso{

    class JudgeData;
    template <typename _Data> class JudgeableObject;
    template <typename _Data> class GameJudgement;

    template <typename _Data>
    bool sortfunc(JudgeableObject<_Data> *i, JudgeableObject<_Data> *j){
        return i->getStartJudgeTime() < j->getStartJudgeTime();
    }

    template <typename _Data>
    bool sortfuncDepth(JudgeableObject<_Data> *i, JudgeableObject<_Data> *j){
        return i->depth() < j->depth();
    }

    class JudgeData:public ILinkTimer{
    public:
        Interface(void startJudge())
        Interface(void endJudge())
        Interface(double getFrameTime())
        Interface(EdpTimer *getTimer())
    };

    template <typename _Data>
    class JudgeableObject{
    public:
        Interface(double getStartJudgeTime())
        Interface(double getEndJudgeTime())
        Interface(void onJudge(_Data *data)) //具体的判定逻辑
        Interface(void onTimeout(_Data *data)) //超时
        Interface(void release()) //判定完了或超时进行释放
        Interface(bool isReleased()) //判断是否被释放
        Interface(int depth()) //物件判定顺序，主要是那些会消耗事件的需要给值
    };

    template <typename _Data>
    class GameJudgement : public IUpdate {
    public:

        explicit GameJudgement(_Data *d){
            data = d;
        }

        void prepare() {
            sort(judgeObjects->begin(), judgeObjects->end(), sortfunc<_Data>);
            judgeObjectsToAdd->clear();
            judgeObjectsToAdd->insert(judgeObjectsToAdd->end(), judgeObjects->begin(), judgeObjects->end());
            judgeObjectsUsing->clear();
        }

        void update() {
            if (data->getTimer()->isRunning()) {
                double time = data->getFrameTime();
                onUpdate();
                data->startJudge();
                updateUsingObjects(time);
                doJudgement(time);
                relaseObjects(time);
                data->endJudge();
                onFinishUpdate();
            }
        }

        void setJudgeObjects(vector<JudgeableObject<_Data> *> *judge) {
            judgeObjects = judge;
            judgeObjectsToAdd = new list<JudgeableObject<_Data> *>();
            judgeObjectsUsing = new vector<JudgeableObject<_Data> *>();
        }

    protected:

        virtual void onUpdate() {}
        virtual void onFinishUpdate() {}

        void updateUsingObjects(double time) {
            bool hasadd = false;
            while ((!judgeObjectsToAdd->empty())) {
                JudgeableObject<_Data> *object = judgeObjectsToAdd->front();
                if (object->getStartJudgeTime() <= time) {
                    judgeObjectsToAdd->pop_front();
                    judgeObjectsUsing->push_back(object);
                    hasadd = true;
                } else {
                    break;
                }
            }
            if (hasadd) {
                sort(judgeObjectsUsing->begin(), judgeObjectsUsing->end(), sortfuncDepth<_Data>);
            }
        }

        virtual void doJudgement(double time){
            ForEach(*judgeObjectsUsing,it,(*it)->onJudge(data), typename vector<JudgeableObject<_Data>*>::iterator)
        }

        void relaseObjects(double time) {
            ForEachLong(*judgeObjectsUsing, it, typename vector<JudgeableObject<_Data> *>::iterator) {
                JudgeableObject<_Data> *object = *it;
                if (object->isReleased()) {
                    it = judgeObjectsUsing->erase(it);
                    it--;
                } else if (object->getEndJudgeTime() < time) {
                    //超时并没有被释放，主动释放
                    object->onTimeout(data);
                    object->release();
                    it = judgeObjectsUsing->erase(it);
                    it--;
                }
            }
        }

    private:
        _Data *data;
        //原始物件
        vector<JudgeableObject<_Data>*> *judgeObjects;
        //还没有被添加的物件
        list<JudgeableObject<_Data>*> *judgeObjectsToAdd;
        //正在判定中的物件
        vector<JudgeableObject<_Data>*> *judgeObjectsUsing;
    };
}



#endif //QT_BB_GAMEJUDGEMENT_H
