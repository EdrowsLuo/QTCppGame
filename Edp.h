//
// Created by admin on 2018/9/6.
//

#ifndef QT_BB_EDP_H
#define QT_BB_EDP_H

#include "defext.h"
#include "direct.h"
#include "EdpTimer.h"
#include "EdpFile.h"
#include "EdpBass.h"

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

    class Project{
    public:
        static EdpFile *ProjectRoot;

        static void initialEdp();
    };
}

#endif //QT_BB_EDP_H
