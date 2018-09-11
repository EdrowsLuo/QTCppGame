//
// Created by admin on 2018/9/10.
//

#include "Edp.h"
#include "CJsonObject.hpp"
#include "IOUtil.h"
#include "BeatmapDecoder.h"
#include "Beatmap.h"

using namespace edp;
using namespace neb;
using namespace nso;

EdpFile * Project::ProjectRoot = new EdpFile(getcwd(new char[300], 300));

void Project::initialEdp() {
    EdpBass::initial();
}

