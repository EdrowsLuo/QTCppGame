//
// Created by admin on 2018/9/16.
//
#include "KeyIO.h"

bool edp::KeyState::isPressed(unsigned int stat) {
    return (stat & Pressed) == Pressed;
}

void edp::KeyState::clearState(unsigned int &state, unsigned int code) {
    state &= ~code;
}

bool edp::KeyEvent::operator<(const edp::KeyEvent &other) const {
    return rawtime > other.rawtime;
}

void edp::QueryKeyInput::start() {
    output = true;
}

bool edp::QueryKeyInput::getKeyEvevnt(edp::KeyEvent &event) {
    if (outputNext()) {
        event = events.back();
        events.erase(events.end() - 1);
        return true;
    } else {
        return false;
    }
}

void edp::QueryKeyInput::end() {
    output = false;
}

bool edp::QueryKeyInput::outputNext() {
    return events.size() > 0;
}

void edp::QueryKeyInput::sortByTime() {
    sort(events.begin(), events.end());
}

vector<edp::KeyEvent> &edp::QueryKeyInput::Events() {
    return events;
}

bool edp::KeyPipe::keyDown(int key, const string &txt) {
    if (!Timer->isRunning()) {
        return false;
    }
    if (output) {
        return false;
    } else {
        double time = Timer->getTime();
        KeyEvent event;
        event.type = KeyState::Down;
        event.key = key;
        event.text = txt;
        event.rawtime = time;
        events.push_back(event);
        return true;
    }
}

bool edp::KeyPipe::keyUp(int key, const string &txt) {
    if (!Timer->isRunning()) {
        return false;
    }
    if (output) {
        return false;
    } else {
        events.push_back(KeyEvent{
                KeyState::Up,
                key,
                txt,
                Timer->getTime()
        });
        return true;
    }
}

void edp::KeyHolder::acceptDownEvent() {
    if (!KeyState::isPressed(State)) {
        State |= KeyState::Down;
        State |= KeyState::Pressed;
    }
}

void edp::KeyHolder::acceptUpEvent() {
    if (KeyState::isPressed(State)) {
        cancel = true;
        State |= KeyState::Up;
    }
}

int edp::KeyHolder::parseMainState() {
    return State & KeyState::MainStateMask;
}

void edp::KeyHolder::consumeEvent() {
    KeyState::clearState(State, KeyState::Down | KeyState::Up);
}

void edp::KeyHolder::pass() {
    if (cancel) {
        cancel = false;
        State = 0;
    }
}

bool edp::KeyHolder::isPressed() {
    return KeyState::isPressed(State);
}

edp::KeyFrame::KeyFrame(edp::KeyInput *in) :
        input(in),
        FrameTime(0) {

}

edp::KeyFrame::KeyFrame():
        input(NULL),
        FrameTime(0) {

}

void edp::KeyFrame::update(double time) {
    FrameTime = time;
    if (input) {
        ForEach(holders,it,it->second->setTime(FrameTime),map<int,KeyHolder*>::iterator)
        KeyEvent event;
        input->start();
        while (input->getKeyEvevnt(event)) {
            map<int,KeyHolder*>::iterator holder = holders.find(event.key);
            if (holder != holders.end()) {
                switch (event.type) {
                    RCase(KeyState::Down, holder->second->acceptDownEvent());
                    DCase(KeyState::Up,holder->second->acceptUpEvent());
                }
                holder->second->setTime(event.rawtime);
            }
        }
        input->end();
    }
}

void edp::KeyFrame::endFrame() {
    ForEach(holders,it,it->second->pass(),map<int,KeyHolder*>::iterator)
}

void edp::KeyFrame::registerHolder(int key, edp::KeyHolder *holder) {
    holders[key] = holder;
}

void edp::KeyFrame::setKeyInput(edp::KeyInput *in) {
    input = in;
}
