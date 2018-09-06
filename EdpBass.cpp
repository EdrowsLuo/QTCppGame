//
// Created by admin on 2018/9/5.
//

#include "EdpBass.h"

using namespace edp;

EdpBassChannel::EdpBassChannel(const string &path) : playing(false) {
    handle = BASS_StreamCreateFile(FALSE, path.c_str(), 0, 0, 0);
}

EdpBassChannel::EdpBassChannel(EdpFile &file) : playing(false) {
    handle = BASS_StreamCreateFile(FALSE, file.getFullPath().c_str(), 0, 0, 0);
}

bool EdpBassChannel::play() {
    playing = true;
    return BASS_ChannelPlay(handle, false);
}

bool EdpBassChannel::isPlaying() {
    return playing;
}

bool EdpBassChannel::pause() {
    playing = false;
    return BASS_ChannelPause(handle);
}

bool EdpBassChannel::stop() {
    playing = false;
    return BASS_ChannelStop(handle);
}

bool EdpBassChannel::seekTo(double ms) {
    return BASS_ChannelSetPosition(handle, BASS_ChannelSeconds2Bytes(handle, ms / 1000.0), BASS_POS_BYTE);
}

double EdpBassChannel::playingTime() {
    return BASS_ChannelBytes2Seconds(handle, BASS_ChannelGetPosition(handle, BASS_POS_BYTE)) * 1000;
}

double EdpBassChannel::getTime() {
    return playingTime();
}

bool EdpBassChannel::isRunning() {
    return playing;
}