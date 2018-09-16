//
// Created by admin on 2018/9/5.
//

#include "EdpBass.h"
#include "Util.h"

using namespace edp;

EdpBassChannel::EdpBassChannel(const string &path) :
        recodeTime(-1L),
        startTime(-1L),
        isPrePlaying(false),
        playing(false){
    handle = BASS_StreamCreateFile(FALSE, path.c_str(), 0, 0, 0);
}

EdpBassChannel::EdpBassChannel(EdpFile &file) :
        recodeTime(-1L),
        startTime(-1L),
        isPrePlaying(false),
        playing(false) {
    handle = BASS_StreamCreateFile(FALSE, file.getFullPath().c_str(), 0, 0, 0);
}

void EdpBassChannel::reset() {
    pause();
    seekTo(0);
    playing = false;
    recodeTime = -1L;
    startTime = -1L;
    isPrePlaying = false;
}

bool EdpBassChannel::play() {
    if (!playing) {
        playing = true;
        if (recodeTime == -1L) {
            //没有暂停，第一次开始
            startTime = util::currentTimeMS();
        } else {
            //从暂停状态恢复
            startTime = util::currentTimeMS() - (recodeTime - startTime);
        }
        return BASS_ChannelPlay(handle, false);
    } else {
        return true;
    }
}

bool EdpBassChannel::isPlaying() {
    return playing || isPrePlaying;
    //return BASS_ChannelIsActive(handle) == BASS_ACTIVE_PLAYING;
}

bool EdpBassChannel::pause() {
    if (playing) {
        playing = false;
        //记录时间
        recodeTime = util::currentTimeMS();
        return BASS_ChannelPause(handle);
    } else {
        return true;
    }
}

bool EdpBassChannel::stop() {
    playing = false;
    recodeTime = -1;
    return BASS_ChannelStop(handle);
}

bool EdpBassChannel::seekTo(double ms) {
    if (playing) {
        startTime = util::currentTimeMS() - (int)ms;
    } else {
        recodeTime = util::currentTimeMS();
        startTime = recodeTime - (int)ms;
    }
    return BASS_ChannelSetPosition(handle, BASS_ChannelSeconds2Bytes(handle, ms / 1000.0), BASS_POS_BYTE);
}

double EdpBassChannel::playingTime() {
    if (isPrePlaying) {
        if (recodeTime == -1L) {
            return util::currentTimeMS() - (postTime + postLength);
        } else {
            return recodeTime - startTime;
        }
    }
    if (playing) {
        return util::currentTimeMS() - startTime;
    } else {
        return recodeTime - startTime;
    }
    //return BASS_ChannelBytes2Seconds(handle, BASS_ChannelGetPosition(handle, BASS_POS_BYTE)) * 1000;
}

double EdpBassChannel::getTime() {
    return playingTime();
}

bool EdpBassChannel::isRunning() {
    //return playing;
    return isPlaying();
}

float EdpBassChannel::getVolume() {
    float data;
    BASS_ChannelGetAttribute(handle, BASS_ATTRIB_VOL, &data);
    return data;
}

bool EdpBassChannel::setVolume(float vol) {
    return BASS_ChannelSetAttribute(handle, BASS_ATTRIB_VOL, vol);
}

double EdpBassChannel::length() {
    return 1000 * BASS_ChannelBytes2Seconds(handle, BASS_ChannelGetLength(handle, BASS_POS_BYTE));
}


void EdpBassChannel::postStart(int ms) {
    isPrePlaying = true;
    postTime = util::currentTimeMS();
    postLength = ms;
}

void EdpBassChannel::update() {
    if (isPrePlaying) {
        if (util::currentTimeMS() - postTime > postLength) {
            play();
            isPrePlaying = false;
        }
    }
}

void EdpBassChannel::release() {
    BASS_StreamFree(handle);
}
