//
// Created by admin on 2018/9/10.
//

#include "Edp.h"

using namespace edp;

EdpFile * Project::ProjectRoot = new EdpFile(getcwd(new char[300], 300));

void Project::initialEdp() {
    EdpBass::initial();
}

