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
    /*CJsonObject object;
    object.AddEmptySubArray("data");

    EdpFile songs(*ProjectRoot, "songs");
    vector<EdpFile> list;
    songs.listFiles(list);

    ForEachLong(list,itr,vector<EdpFile>::iterator) {
        if (itr->isDirectory()) {
            CJsonObject beatmapSet;
            beatmapSet.Add("file", itr->getName());
            beatmapSet.AddEmptySubArray("data");
            vector<EdpFile> osus;
            itr->listFiles(osus);
            bool first = false;
            ForEachLong(osus,osu,vector<EdpFile>::iterator) {
                if (osu->isFile() && (osu->getName().find(".osu") != string::npos)) {
                    DebugI("start decode : " << osu->getFullPath())

                    //EdpFileReader reader(*osu);
                    string data;
                    IOUtil::readFull(*osu, data);


                    Beatmap beatmap;
                    BeatmapDecoder decoder(*osu);
                    try {
                        decoder.parse(beatmap);
                        decoder.close();
                    } catch (DecodeException& e) {
                        DebugI("err " << e.what())
                        continue;
                    }

                    if (!first) {
                        first = true;
#define AddDataX(name) beatmapSet.Add(#name, beatmap.name);
                        AddDataX(Artist)
                        AddDataX(Title)
                        AddDataX(Creator)
                    }

                    CJsonObject osudata;
                    osudata.Add("file", osu->getName());
                    osudata.Add("star", 3.43);
#define AddData(name) osudata.Add(#name, beatmap.name);
                    AddData(BackgroundFile)
                    AddData(Title)
                    AddData(Artist)
                    AddData(Creator)
                    AddData(Version)
                    AddData(CircleSize)
                    AddData(OverallDifficulty)
                    AddData(AudioLeadIn)
                    AddData(PreviewTime)
                    beatmapSet["data"].Add(osudata);
                }
            }
            object["data"].Add(beatmapSet);
        }
    }





    EdpFile out(*ProjectRoot, "songs\\songs.json");
    *//*string str;
    IOUtil::readFull(out, str);
    CJsonObject object(str);
    //DebugI(object["data"].IsArray())
    CJsonObject set;
    object["data"].Get(0,set);
    CJsonObject settt;
    set["data"].Get(0, settt);

    string xxx;
    set.Get("file", xxx);*//*




    if (!out.exist()) {
        out.createNewFileWithDir();
    }
    IOUtil::writeFull(out, object.ToFormattedString());*/
}

