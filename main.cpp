#include <QtGui/QApplication>
#include <iostream>
#include "mainwindow.h"
#include "BaseDecoder.h"
#include "StringUtil.h"
#include "BeatmapDecoder.h"
#include "EdpBass.h"
#include "dialog.h"
#include <QDebug>
#include <QMessageBox>
#include <bass.h>
#include "defext.h"
#include "IOUtil.h"
#include "CJsonObject.hpp"
#include "Project.h"

using namespace std;
using namespace nso;
using namespace edp;
using namespace neb;


LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException){//程式异常捕获
    /*
      ***保存数据代码***
    */
    //这里弹出一个错误对话框并退出程序
    EXCEPTION_RECORD* record = pException->ExceptionRecord;
    QString errCode(QString::number(record->ExceptionCode,16)),errAdr(QString::number((uint)record->ExceptionAddress,16)),errMod;
    QMessageBox::critical(NULL,"程式崩溃","<FONT size=4><div><b>对于发生的错误，表示诚挚的歉意</b><br/></div>"+
                                      QString("<div>错误代码：%1</div><div>错误地址：%2</div></FONT>").arg(errCode).arg(errAdr),
                          QMessageBox::Ok);
    return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char *argv[])
{
    Debug("start");

    Game_Initial

//#define OUT_JSON
#ifdef OUT_JSON
    CJsonObject object;
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





    EdpFile out(*Project::ProjectRoot, "assets\\songs\\songs.json");
    /*string str;
    IOUtil::readFull(out, str);
    CJsonObject object(str);
    //DebugI(object["data"].IsArray())
    CJsonObject set;
    object["data"].Get(0,set);
    CJsonObject settt;
    set["data"].Get(0, settt);

    string xxx;
    set.Get("file", xxx);*/
    if (!out.exist()) {
        out.createNewFileWithDir();
    }
    IOUtil::writeFull(out, object.ToFormattedString());
#endif








    QApplication a(argc, argv);


    DebugI(Project::ProjectRoot->getFullPath())

    Dialog dialog;
    dialog.show();

    Debug("end");
    return a.exec();
}
