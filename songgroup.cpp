#include "songgroup.h"
using namespace neb;
using namespace nso;

SongGroup::SongGroup()
{
    EdpFile out(*Project::ProjectRoot,"assets\\songs\\songs.json");
    string str;
    IOUtil::readFull(out, str);
    CJsonObject holeFile(str);
    Number=holeFile["data"].GetArraySize();
  //  DebugL("l")
    songlist = new My_Song[Number];
  //  DebugL("s")
    CJsonObject *jsong = new CJsonObject[Number];
  //  DebugL("d")
    for (int i = 0; i < Number; i++ ) {
        holeFile["data"].Get(i,jsong[i]);
  //          DebugL("m")
        songlist[i] = My_Song(jsong[i]);

    }

    delete jsong;
/*    namelist = new string[Number];
    creatorlist = new string[Number];
    song = new CJsonObject[Number];

    for ( int i = 0 ; i < Number ; i++ ){
        holeFile["data"].Get(i,song[i]);
        song[i].Get("Artist",namelist[i]);
        song[i].Get("Creator",creatorlist[i]);
        song[i].Get("Title",titlelist[i]);
        int difficultyset = song[i].GetArraySize();
        CJsonObject *difficulty;
        difficulty = new CJsonObject[difficultyset];

        string *jstar,*jbackgroundfile,*jversion;
        int *jcirclesize,*joveralldifficulty,*jaudioleadin;
        jstar = new string[difficultyset];
        jbackgroundfile = new string[difficultyset];
        jversion = new string[difficultyset];
        jcirclesize = new int[difficultyset];
        joveralldifficulty = new int[difficultyset];
        jaudioleadin = new int[difficultyset];

        for ( int j = 0 ; j <difficultyset ; j++ ){
            song[i].Get(j,difficulty[j]);
            difficulty[j].Get("Star",jstar[j]);
            difficulty[j].Get("BackgroundFile",jbackgroundfile[j]);
            difficulty[j].Get("Version",jversion[j]);
            difficulty[j].Get("CircleSize",jcirclesize[j]);
            difficulty[j].Get("OverallDifficulty",joveralldifficulty[j]);
            difficulty[j].Get("AudioLeadIn",jaudioleadin[j]);

        }
    }
            */

}
