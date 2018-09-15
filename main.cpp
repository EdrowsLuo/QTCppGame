#include <QtGui/QApplication>
#include "mainwindow.h"
#include "Project.h"


int main(int argc, char *argv[])
{
    Game_Initial





   /* CJsonObject object;
    object.AddEmptySubArray("data");

    EdpFile songs(*Project::ProjectRoot, "assets\\songs");
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
                    osudata.Add("length", beatmap.avalibleLength());
#define AddData(name) osudata.Add(#name, beatmap.name);
                    AddData(AudioFilename)
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





    EdpFile out(*Project::ProjectRoot, "assets\\songs\\songs.json");
    if (!out.exist()) {
        out.createNewFileWithDir();
    }
    IOUtil::writeFull(out, object.ToFormattedString());*/








    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    
    return a.exec();
}
