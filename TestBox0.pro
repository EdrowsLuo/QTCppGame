#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T10:00:55
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

TARGET = TestBox0
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    slidebox1.cpp \
    slideanim.cpp \
    difficultyscrollarea.cpp \
    myqsplitter.cpp \
    EdpFileWriter.cpp \
    EdpFileReader.cpp \
    EdpFile.cpp \
    EdpBass.cpp \
    Edp.cpp \
    CJsonObject.cpp \
    cJSON.cpp \
    IOUtil.cpp \
    difficultyframe.cpp \
    rightframe.cpp \
    songgroup.cpp \
    my_song.cpp \
    my_difficulty.cpp \
    Project.cpp \
    leftframe.cpp \
    widgettest.cpp \
    ManiaRuleset.cpp \
    ManiaObjects.cpp \
    GameJudgement.cpp \
    BeatmapSetLoader.cpp \
    BeatmapSetData.cpp \
    BeatmapDecoder.cpp \
    Beatmap.cpp \
    BaseDecoder.cpp \
    shadow.cpp

HEADERS  += mainwindow.h \
    slidebox1.h \
    slideanim.h \
    difficultyscrollarea.h \
    myqsplitter.h \
    defext.h \
    types.h \
    EdpTimer.h \
    EdpFileWriter.h \
    EdpFileReader.h \
    EdpFile.h \
    EdpBass.h \
    Edp.h \
    CJsonObject.hpp \
    cJSON.h \
    IOUtil.h \
    difficultyframe.h \
    rightframe.h \
    songgroup.h \
    my_song.h \
    my_difficulty.h \
    Project.h \
    leftframe.h \
    widgettest.h \
    Util.h \
    StringUtil.h \
    nsoclass.h \
    ManiaRuleset.h \
    ManiaObjects.h \
    maniaclass.h \
    KeyIO.h \
    GameJudgement.h \
    BeatmapSetLoader.h \
    BeatmapSetData.h \
    BeatmapDecoder.h \
    BeatmapBase.h \
    Beatmap.h \
    bassclass.h \
    BaseDecoder.h \
    shadow.h \
    MyDraw.h

FORMS    += mainwindow.ui \
    slidebox1.ui \
    difficultyscrollarea.ui \
    difficultyframe.ui \
    rightframe.ui

LIBS += -L F:\qt\QTCppGame -l bass

RESOURCES += \
    background.qrc
