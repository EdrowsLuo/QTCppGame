//
// Created by admin on 2018/9/6.
//

#include "ManiaRuleset.h"
#include "KeyIO.h"

using namespace nso;

double MainaPlaytimeData::getFrameTime() {
    return frameTime;
}

EdpTimer* MainaPlaytimeData::getTimer() {
    return timer;
}

void MainaPlaytimeData::update() {
    if (timer->isRunning()) {
        MKeyFrame->update(); //更新键盘状态
        frameTime = MKeyFrame->getFrameTime();
    }
}

void MainaPlaytimeData::endJudge() {
    if (timer->isRunning()) {
        MKeyFrame->endFrame();
    }
}