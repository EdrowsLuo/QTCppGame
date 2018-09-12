//
// Created by admin on 2018/9/12.
//

#include "Project.h"

using namespace nso;

//EdpFile * Project::ProjectRoot = new EdpFile(getcwd(new char[300], 300));

EdpFile *Project::ProjectRoot = NULL;
GameHolder *Project::ProjectGame = new GameHolder();

void nso::Project::initialProject() {
    EdpBass::initial();
}
