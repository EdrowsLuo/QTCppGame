#ifndef MY_DIFFICULTY_H
#define MY_DIFFICULTY_H
#include"Edp.h"
#include "EdpFile.h"
#include "IOUtil.h"
#include <string.h>
#include "cJSON.h"
#include "CJsonObject.hpp"

using namespace neb;

class My_Difficulty
{
public:
    My_Difficulty( CJsonObject );
    My_Difficulty(){};
    string file,backgroundfile,version,audiofilename;
    int previewtime,circlesize,overalldifficulty,audioleadin,lenth;
    double star;

};

#endif // MY_DIFFICULTY_H
