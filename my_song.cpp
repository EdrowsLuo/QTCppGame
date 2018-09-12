#include "my_song.h"

My_Song::My_Song( CJsonObject jsong )
{
    DebugL("m1")
    difficultyset = jsong["data"].GetArraySize();

    songsName = "untitled";

    difficultylist = new My_Difficulty[difficultyset];
    CJsonObject *jdifficulty = new CJsonObject[difficultyset];
    jsong.Get("Artist",artistName);
    jsong.Get("Creator",creatorName);
    jsong.Get("Title",songsName);
    DebugL("m2")
 //   DebugL(songsName.c_str())
 //   DebugL("m2.5")
    for (int j = 0; j < difficultyset; j++ ) {
  //          DebugL("m2.8")
        jsong["data"].Get(j,jdifficulty[j]);
 //           DebugL("m3")
        difficultylist[j] = My_Difficulty(jdifficulty[j]);
    }
//                DebugL("m2.10")
    delete jdifficulty;
}
