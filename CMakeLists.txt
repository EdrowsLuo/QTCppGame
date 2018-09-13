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
        background.cpp
        background.h
        BaseDecoder.cpp
        BaseDecoder.h
        bassclass.h
        Beatmap.cpp
        Beatmap.h
        BeatmapBase.h
        BeatmapDecoder.cpp
        BeatmapDecoder.h
        BeatmapSetData.cpp
        BeatmapSetData.h
        BeatmapSetLoader.cpp
        BeatmapSetLoader.h
        calscore.cpp
        calscore.h
        cJSON.h
        cJSON.cpp
        CJsonObject.hpp
        CJsonObject.cpp
        coordinate.cpp
        coordinate.h
        defext.h
        difficultyframe.h
        difficultyframe.cpp
        difficultyscrollarea.cpp
        difficultyscrollarea.h
        drawtext.cpp
        drawtext.h
        Edp.cpp
        Edp.h
        EdpBass.cpp
        EdpBass.h
        EdpFile.cpp
        EdpFile.h
        EdpFileReader.cpp
        EdpFileReader.h
        EdpFileWriter.cpp
        EdpFileWriter.h
        EdpTimer.h
        GameJudgement.cpp
        GameJudgement.h
        IOUtil.h
        IOUtil.cpp
        judgescore.cpp
        judgescore.h
        KeyIO.h
        keys.cpp
        keys.h
        leftframe.h
        leftframe.cpp
        main.cpp
        mainwindow.h
        mainwindow.cpp
        maniaclass.h
        ManiaObjects.cpp
        ManiaObjects.h
        ManiaRuleset.cpp
        ManiaRuleset.h
        my_difficulty.cpp
        my_difficulty.h
        my_song.cpp
        my_song.h
        mycombo.cpp
        mycombo.h
        MyDraw.h
        myqsplitter.cpp
        myqsplitter.h
        myscore.cpp
        myscore.h
        nsoclass.h
        parsers.cpp
        parsers.h
        pixmapmanager.cpp
        pixmapmanager.h
        progressbar.cpp
        progressbar.h
        Project.cpp
        Project.h
        rankingbg.cpp
        rankingbg.h
        rhythmline.cpp
        rhythmline.h
        rightframe.cpp
        rightframe.cpp
        shadow.cpp
        shadow.h
        slideanim.h
        slideanim.cpp
        slidebox1.cpp
        slidebox1.h
        songgroup.h
        songgroup.cpp
        songs.cpp
        songs.h
        squaredown.cpp
        squaredown.h
        squaredownh.cpp
        squaredownh.h
        StringUtil.h
        tracke.cpp
        tracke.h
        types.h
        Util.h
        widget.cpp
        widget.h
        widget1.cpp
        widget1.h
        widgettest.cpp
        widgettest.h
        )

target_link_libraries(qt_bb ${QT_LIBRARIES} )

target_link_libraries(qt_bb bass)