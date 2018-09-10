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

#define Game_Initial char *tmp = new char[MAX_PATH];\
GetModuleFileNameA(NULL, tmp, MAX_PATH);\
edp::Project::ProjectRoot = new edp::EdpFile(tmp);\
edp::Project::ProjectRoot = new edp::EdpFile(edp::Project::ProjectRoot->getParentPath());\
edp::Project::initialEdp();

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
