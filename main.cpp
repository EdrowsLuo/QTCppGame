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

using namespace std;
using namespace nso;


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
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    EdpBass::initial();

    Dialog dialog;
    dialog.show();

    BeatmapDecoder decoder("D:\\Qt\\code\\qt_bb\\data\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [Starry's 4K Lv.15].osu");
    Beatmap beatmap;
    try {
        decoder.parse(beatmap);
    } catch (DecodeException &e) {
        DebugS << "DecodeException : " << e.what();
    }

    Debug("end");
    return a.exec();
}
