#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T19:30:29
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

TARGET = MYFDK
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    background.cpp \
    tracke.cpp \
    mycombo.cpp \
    keys.cpp\
    BaseDecoder.cpp\
    Edp.cpp\
    EdpFile.cpp\
    EdpFileReader.cpp\
    EdpFileWriter.cpp\
    IOUtil.cpp\
    Beatmap.cpp\
    parsers.cpp\
    BeatmapDecoder.cpp\
    EdpBass.cpp\
    GameJudgement.cpp\
    ManiaRuleset.cpp\
    ManiaObjects.cpp \
    myscore.cpp \
    coordinate.cpp \
    squaredown.cpp \
    squaredownh.cpp \
    shadow.cpp \
    progressbar.cpp \
    rhythmline.cpp\
    Project.cpp

HEADERS  += widget.h \
    MyDraw.h \
    background.h \
    tracke.h \
    mycombo.h \
    keys.h\
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
    defext.h\
    KeyIO.h\
    EdpTimer.h\
    GameJudgement.h\
    Edp.h\
    ManiaRuleset.h\
    maniaclass.h\
    ManiaObjects.h\
    BeatmapBase.h\
    Util.h \
    myscore.h \
    coordinate.h \
    squaredown.h \
    squaredownh.h \
    shadow.h \
    progressbar.h \
    rhythmline.h\
    Project.h






FORMS    += widget.ui


LIBS += -L D:\QT\wj\MyBKG -l bass
