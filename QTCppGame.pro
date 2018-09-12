#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T10:00:55
#
#-------------------------------------------------

QT       += core gui
QT          += opengl

TARGET = QTCppGame
TEMPLATE = app


SOURCES += \
    main.cpp\
    mainwindow.cpp \
    \
    \
    \
    \
    slidebox1.cpp \
    slideanim.cpp \
    difficultyscrollarea.cpp \
    myqsplitter.cpp \
    difficultyframe.cpp \
    rightframe.cpp \
    songgroup.cpp \
    my_song.cpp \
    my_difficulty.cpp \
    leftframe.cpp\
    \
    \
    \
    \
    BaseDecoder.cpp \
    EdpFile.cpp \
    EdpFileReader.cpp \
    EdpFileWriter.cpp \
    IOUtil.cpp \
    Beatmap.cpp \
    parsers.cpp \
    BeatmapDecoder.cpp \
    EdpBass.cpp \
    GameJudgement.cpp \
    ManiaRuleset.cpp \
    ManiaObjects.cpp \
    Edp.cpp \
    Project.cpp \
    \
    \
    \
    \
    \
    cJSON.cpp\
    CJsonObject.cpp\




HEADERS  += \
    mainwindow.h \
    slidebox1.h \
    slideanim.h \
    difficultyscrollarea.h \
    myqsplitter.h \
    difficultyframe.h \
    rightframe.h \
    songgroup.h \
    my_song.h \
    my_difficulty.h \
    leftframe.h\
    \
    \
    \
    \
    \
    \
    BaseDecoder.h \
    EdpFile.h \
    EdpFileReader.h \
    EdpFileWriter.h \
    IOUtil.h \
    Beatmap.h \
    StringUtil.h \
    parsers.h \
    BeatmapDecoder.h \
    nsoclass.h \
    EdpBass.h \
    bassclass.h \
    defext.h \
    KeyIO.h \
    EdpTimer.h \
    GameJudgement.h \
    Edp.h \
    ManiaRuleset.h \
    maniaclass.h \
    ManiaObjects.h \
    BeatmapBase.h \
    Util.h \
    Project.h \
    \
    \
    \
    \
    \
    CJsonObject.hpp \
    cJSON.h \



FORMS    += mainwindow.ui \
    slidebox1.ui \
    difficultyscrollarea.ui \
    difficultyframe.ui \
    rightframe.ui

CONFIG +=console

LIBS += -L D:/Qt/code/qt_bb -l bass
