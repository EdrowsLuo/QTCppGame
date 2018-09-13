//
// Created by admin on 2018/9/12.
//

#ifndef QT_BB_PROJECT_H
#define QT_BB_PROJECT_H

#include "EdpFile.h"
#include "ManiaRuleset.h"


#define Game_Initial char *tmp = new char[MAX_PATH];\
GetModuleFileNameA(NULL, tmp, MAX_PATH);\
nso::Project::ProjectRoot = new edp::EdpFile(tmp);\
nso::Project::ProjectRoot = new edp::EdpFile(nso::Project::ProjectRoot->getParentPath());\
nso::Project::initialProject();\
nso::Project::ProjectGame = new nso::GameHolder();



using namespace edp;

namespace nso{
    class Project{
    public:
        static EdpFile *ProjectRoot;

        static GameHolder *ProjectGame;

        static string fromRoot(const string &path);

        static QString fromRootQ(const string &path);

        static void initialProject();
    };
}



#endif //QT_BB_PROJECT_H
