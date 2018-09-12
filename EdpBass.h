//
// Created by admin on 2018/9/5.
//

#ifndef QT_BB_EDPBASS_H
#define QT_BB_EDPBASS_H

#include <bass.h>
#include "EdpFile.h"
#include "bassclass.h"
#include "EdpTimer.h"

namespace edp{

    class EdpBass {
    public:
        static void initial(){
            BASS_Init(-1, 44100, 0, 0, NULL);
        }
    };

    class EdpBassChannel : public EdpTimer{
    public:
        explicit EdpBassChannel(const string &path);
        explicit EdpBassChannel(EdpFile &file);

        bool isPlaying();
        bool play();
        bool pause();
        bool stop();
        bool seekTo(double ms);
        double playingTime();
        float getVolume();
        bool setVolume(float vol);
        double length();

        void reset();

        void release();

        void postStart(int ms);
        void update();
        void setOffset(int ms) {
            offset = ms;
        }

        double getTime();
        bool isRunning();

    protected:
        DWORD handle;

        long long recodeTime;
        long long startTime;

        int offset;
        bool isPrePlaying;
        long long postTime;
        int postLength;

        bool playing;
    };
}



#endif //QT_BB_EDPBASS_H
