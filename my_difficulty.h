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
    string star,backgroundfile,version;
    int circlesize,overalldifficulty,audioleadin;

};

#endif // MY_DIFFICULTY_H
