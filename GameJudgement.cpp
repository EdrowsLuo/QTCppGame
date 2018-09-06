//
// Created by admin on 2018/9/6.
//

#include "GameJudgement.h"
#include <algorithm>
#include "defext.h"

using namespace nso;

namespace nso{
    template <typename _Data>
    bool sortfunc(JudgeableObject<_Data> *i, JudgeableObject<_Data> *j){
        return i->getStartJudgeTime() < j->getStartJudgeTime();
    }

    template <typename _Data>
    bool sortfuncDepth(JudgeableObject<_Data> *i, JudgeableObject<_Data> *j){
        return i->depth() < j->depth();
    }
}

template<typename _Data>
GameJudgement<_Data>::GameJudgement(_Data *d):data(d) {

}

template <typename _Data>
void GameJudgement<_Data>::prepare() {
    sort(judgeObjects.begin(), judgeObjects.end(), sortfunc);
    judgeObjectsToAdd.clear();
    judgeObjectsToAdd.insert(judgeObjectsToAdd.end(), judgeObjects.begin(), judgeObjects.end());
    judgeObjectsUsing.clear();
}

template <typename _Data>
void GameJudgement<_Data>::update() {
    if (data->getTimer()->isRunning()) {
        double time = data->getFrameTime();
        onUpdate();
        updateUsingObjects(time);
        doJudgement(time);
        relaseObjects(time);
        data->endJudge();
        onFinishUpdate();
    }
}

template <typename _Data>
void GameJudgement<_Data>::updateUsingObjects(double time) {
    bool hasadd = false;
    while ((!judgeObjectsToAdd.empty())) {
        JudgeableObject<_Data> *object = judgeObjectsToAdd.front();
        if (object->getStartJudgeTime() >= time) {
            judgeObjectsToAdd.pop_front();
            judgeObjectsUsing.push_back(object);
            hasadd = true;
        } else {
            break;
        }
    }
    if (hasadd) {
        sort(judgeObjectsUsing.begin(), judgeObjectsUsing.end(), sortfuncDepth);
    }
}

template <typename _Data>
void GameJudgement<_Data>::doJudgement(double time) {
    ForEach(judgeObjectsUsing,it,(*it)->onJudge(data), typename vector<JudgeableObject<_Data>*>::iterator)
}

template <typename _Data>
void GameJudgement<_Data>::relaseObjects(double time) {
    ForEachLong(judgeObjectsUsing,it, typename vector<JudgeableObject<_Data>*>::iterator) {
            JudgeableObject<_Data> *object = *it;
            if (object->getEndJudgeTime() < time && !object->isReleased()) {
                //超时并没有被释放，主动释放
                object->release();
                it = judgeObjectsUsing.erase(it);
            } else if (object->isReleased()) {
                it = judgeObjectsUsing.erase(it);
            }
    }}
}