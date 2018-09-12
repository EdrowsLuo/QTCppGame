#include "my_difficulty.h"

My_Difficulty::My_Difficulty( CJsonObject jdifficulty )
{
    star = "ss";
    jdifficulty.Get("star",star);
    jdifficulty.Get("BackgroundFile",backgroundfile);
    jdifficulty.Get("Version",version);
    jdifficulty.Get("CircleSize",circlesize);
    jdifficulty.Get("OverallDifficulty",overalldifficulty);
    jdifficulty.Get("AudioLeadIn",audioleadin);
}
