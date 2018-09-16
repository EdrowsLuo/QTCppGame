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
    setting.cpp\
    \
    \
    \
    \
    BaseDecoder.cpp \
    EdpFile.cpp \
    EdpFileReader.cpp \
    EdpFileWriter.cpp \
    IOUtil.cpp \
    KeyIO.cpp\
    Beatmap.cpp \
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
    \
    widget.cpp \
        background.cpp \
        tracke.cpp \
        mycombo.cpp \
        keys.cpp\
        myscore.cpp \
        coordinate.cpp \
        squaredown.cpp \
        squaredownh.cpp \
        shadow.cpp \
        progressbar.cpp \
        rhythmline.cpp\
        judgescore.cpp \
        calscore.cpp \
        judgescore2.cpp\
        addcas.cpp\
        rankingpic.cpp\
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
    setting.h\
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
    easing.h\
    addcas.h\
    rankingpic.h\
    \
    \
    \
    \
    widget.h \
    MyDraw.h \
        background.h \
        tracke.h \
        mycombo.h \
        keys.h\
        myscore.h \
        coordinate.h \
        squaredown.h \
        squaredownh.h \
        shadow.h \
        progressbar.h \
        rhythmline.h\
        judgescore.h \
        calscore.h \
        judgescore2.h\
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

FORMS    += widget.ui


RESOURCES += \
    background.qrc

LIBS += -L D:\QT\wj\QTCppGame-release-working -l bass
