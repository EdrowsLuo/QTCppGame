#ifndef SONGGROUP_H
#define SONGGROUP_H

#include "Project.h"
#include "EdpFile.h"
#include "IOUtil.h"
#include "string.h"
#include "cJSON.h"
#include "CJsonObject.hpp"
#include "my_song.h"

using namespace neb;
class SongGroup
{
public:
    SongGroup();
    int Number;
    My_Song *songlist;
    /*string *namelist,*creatorlist,*titlelist;
    CJsonObject *song;*/



};

#endif // SONGGROUP_H
