#-------------------------------------------------
#
# Project created by QtCreator 2018-09-03T21:47:34
#
#-------------------------------------------------

QT       += core gui
QT          += opengl

TARGET = qt_bb
TEMPLATE = app




SOURCES += main.cpp\
        mainwindow.cpp\
        BaseDecoder.cpp\
        EdpFile.cpp\
        EdpFileReader.cpp\
        EdpFileWriter.cpp\
        IOUtil.cpp\
        Beatmap.cpp\
        parsers.cpp\
        BeatmapDecoder.cpp\
        EdpBass.cpp\
        dialog.cpp\
        GameJudgement.cpp\
        ManiaRuleset.cpp\
        TestView.cpp\
        ManiaObjects.cpp\
        Edp.cpp\
        cJSON.cpp\
        CJsonObject.cpp

HEADERS  += mainwindow.h\
        BaseDecoder.h\
        EdpFile.h\
        EdpFileReader.h\
        EdpFileWriter.h\
        IOUtil.h\
        Beatmap.h\
        StringUtil.h\
        parsers.h\
        BeatmapDecoder.h\
        nsoclass.h\
        EdpBass.h\
        bassclass.h \
        dialog.h\
        defext.h\
        KeyIO.h\
        EdpTimer.h\
        GameJudgement.h\
        Edp.h\
        ManiaRuleset.h\
        TestView.h\
        maniaclass.h\
        ManiaObjects.h\
        BeatmapBase.h\
        Util.h\
        CJsonObject.hpp\
        cJSON.h


FORMS    += mainwindow.ui \
    dialog.ui

CONFIG +=console

LIBS += -L D:/Qt/code/qt_bb -l bass
