cmake_minimum_required(VERSION 3.10)
project(qt_bb)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR  on)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL)
include(${QT_USE_FILE})
include_directories(${Qt4_INCLUDE_DIRECTORIES})
include_directories(/usr/include)
QT4_WRAP_UI(UI Window.ui)
QT4_WRAP_CPP(UI_CPP  Window.h Window.cpp)

include_directories(D:/Qt/code/qt_bb/include)
link_directories(D:/Qt/code/qt_bb/lib)
link_libraries(bass)

add_executable(qt_bb
        main.cpp
        mainwindow.cpp
        mainwindow.h
        BaseDecoder.cpp
        BaseDecoder.h
        EdpFile.h
        EdpFile.cpp
        EdpFileReader.cpp
        EdpFileReader.h
        EdpFileWriter.cpp
        EdpFileWriter.h
        IOUtil.cpp
        IOUtil.h
        Beatmap.cpp
        Beatmap.h
        StringUtil.h
        parsers.cpp
        parsers.h
        BeatmapDecoder.cpp
        BeatmapDecoder.h
        nsoclass.h
        EdpBass.cpp
        EdpBass.h
        bassclass.h
        dialog.cpp
        dialog.h
        dialog.ui
        KeyIO.h
        defext.h
        EdpTimer.h
        GameJudgement.cpp
        GameJudgement.h
        Edp.h
        ManiaRuleset.cpp
        ManiaRuleset.h
        TestView.cpp
        TestView.h
        maniaclass.h
        ManiaObjects.cpp
        ManiaObjects.h
        BeatmapBase.h
        Util.h
        Edp.cpp
        BeatmapSetLoader.cpp
        BeatmapSetLoader.h
        BeatmapSetData.cpp
        BeatmapSetData.h
        cJSON.h
        cJSON.cpp
        CJsonObject.cpp
        CJsonObject.hpp)
target_link_libraries(qt_bb ${QT_LIBRARIES} )

target_link_libraries(qt_bb bass)