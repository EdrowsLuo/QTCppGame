#ifndef MY_SONG_H
#define MY_SONG_H

#include"Edp.h"
#include "EdpFile.h"
#include "IOUtil.h"
#include <string.h>
#include "cJSON.h"
#include "CJsonObject.hpp"
#include "my_difficulty.h"

using namespace neb;

class My_Song
{
public:
    My_Song( CJsonObject );
    My_Song(){};
    int difficultyset;
    My_Difficulty *difficultylist;
    string songsName,creatorName,artistName;
};

#endif // MY_SONG_H
