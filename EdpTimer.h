//
// Created by admin on 2018/9/5.
//

#ifndef QT_BB_EDPTIMER_H
#define QT_BB_EDPTIMER_H

#include "defext.h"

namespace edp{
    class EdpTimer{
    public:
        Interface(double getTime())
        Interface(bool isRunning())
    };
}

#endif //QT_BB_EDPTIMER_H
