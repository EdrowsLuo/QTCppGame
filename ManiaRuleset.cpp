//
// Created by admin on 2018/9/6.
//

#include <algorithm>
#include "ManiaRuleset.h"
#include "KeyIO.h"

using namespace nso;

double ManiaPlaytimeData::getFrameTime() {
    return frameTime;
}

EdpTimer* ManiaPlaytimeData::getTimer() {
    return timer;
}

void ManiaPlaytimeData::update() {
    if (timer->isRunning()) {
        MKeyFrame->update(); //更新键盘状态
        frameTime = MKeyFrame->getFrameTime();
    }
}

void ManiaPlaytimeData::endJudge() {
    if (timer->isRunning()) {
        MKeyFrame->endFrame();
    }
}

ManiaDrawdata::ManiaDrawdata(nso::Beatmap &beatmap) : Preempt(400), LineCount((int) (beatmap.CircleSize + 0.01)) {
    ForEachLong(beatmap.hitobjects, it, vector<HitObject*>::iterator) {
            HitObject *object = *it;
            if ((object->type & HitObject::TYPE_MASK) == HitObject::TYPE_MANIA_HOLD) {
                rawObjects.push_back(new PlayingHold((ManiaHold &) *object));
                stringstream ss;
                ss << " raw start: " << ((ManiaHold &) *object).time << "  end: " << ((ManiaHold &) *object).endTime;
                //Debug(it->toString().c_str());
            } else {
                rawObjects.push_back(new PlayingNote((HitCircle &) *object));
            }
        }}
        /*DebugI(LineCount)*/
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
        }}

    //开始组织数据
    datas.clear();
    ForEachLong(objectsUsing, it, vector<PlayingHitObject*>::iterator) {
            PlayingHitObject *object = *it;
            if (object->getType() == HitObject::TYPE_MANIA_HOLD) {
                float t =  (object->getTime()-(float)time)/Preempt;
                t = Clamp(0, t, 1);
                float t2 =  (object->getEndTime()-(float)time)/Preempt;
                t2 = Clamp(0, t2, 1);
                datas.push_back(ManiaDrawdataNode{
                        object,
                        object->getType(),
                        ManiaUtil::positionToLine(object->getX(), LineCount),
                        t,
                        t2
                });
            } else {
                float t =  (object->getTime()-(float)time)/Preempt;
                t = Clamp(0, t, 1);
                datas.push_back(ManiaDrawdataNode{
                        object,
                        object->getType(),
                        ManiaUtil::positionToLine(object->getX(), LineCount),
                        t,
                        t
                });
            }
        }}
}

PlayingHitObject::PlayingHitObject(HitObject &h) :
        released(false),
        X(h.x),
        Y(h.y),
        Time(h.time),
        Type(h.type),
        HitSound(h.hitSound) {
    /*stringstream ss;
    ss << "raw: " << h.x << " line: " << ManiaUtil::positionToLine(getX(), 4);
    Debug(ss.str().c_str());*/
}
