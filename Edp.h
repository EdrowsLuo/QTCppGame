//
// Created by admin on 2018/9/6.
//

#ifndef QT_BB_EDP_H
#define QT_BB_EDP_H

#include "defext.h"
#include "EdpTimer.h"

#define GAME_RELEASE

namespace edp{
    class IUpdate{
        Interface(void update())
    };

    class IUpdateByTime{
        Interface(void update(double time))
    };

    class ILinkTimer{
        Interface(EdpTimer *getTimer())
    };
}

#endif //QT_BB_EDP_H
