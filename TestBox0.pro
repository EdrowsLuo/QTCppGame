#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T10:00:55
#
#-------------------------------------------------

QT       += core gui

TARGET = TestBox0
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    slidebox1.cpp \
    slideanim.cpp \
    difficultyscrollarea.cpp \
    myqsplitter.cpp \
    songs.cpp \
    EdpFileWriter.cpp \
    EdpFileReader.cpp \
    EdpFile.cpp \
    EdpBass.cpp \
    Edp.cpp \
    CJsonObject.cpp \
    cJSON.cpp \
    IOUtil.cpp

HEADERS  += mainwindow.h \
    slidebox1.h \
    slideanim.h \
    difficultyscrollarea.h \
    myqsplitter.h \
    songs.h \
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
    IOUtil.h

FORMS    += mainwindow.ui \
    slidebox1.ui \
    difficultyscrollarea.ui

LIBS += -L F:\qt\QTCppGame -l bass
