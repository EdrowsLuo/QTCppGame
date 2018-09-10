//
// Created by admin on 2018/9/5.
//

#ifndef QT_BB_KEYINPUT_H
#define QT_BB_KEYINPUT_H

#include <string>
#include <map>
#include <QtGui/QKeyEvent>
#include "EdpTimer.h"
#include "defext.h"
#include <algorithm>

using namespace std;

/**
 *
 *
 *
 */
#define USING_QT
namespace edp{
    /**
     * 键盘输入
     */
    class KeyInput;

    class QueryKeyInput;

    class KeyPipe;

    class NativeKeyPipe;
#ifdef USING_QT
    class QTKeyPipe;
#endif
    /**
     * 键盘输出
     */
    class KeyOutput;

    class KeyEvent;

    /**
     * 捕获对某个或某些键的事件并保存相关数据
     */
    class KeyHolder;

    /**
     * 单帧事件，包含多个KeyHolder，通过从一个KeyInput读取事件来刷新
     */
    class KeyFrame;

    class KeyState;

    class KeyState{
    public:
        static const unsigned int Pressed  = 1;
        static const unsigned int Down = 2;
        static const unsigned int Up = 4;
        static const unsigned int MainStateMask = Down + Up;

        static bool isPressed(unsigned int stat){
            return (stat & Pressed) == Pressed;
        }

        static void clearState(unsigned int &state, unsigned int code) {
            state &= ~code;
        }

    };

    class KeyEvent{
    public:
        int type;
        int key;
        string text;
        double rawtime;

        bool operator<(const KeyEvent &other) const {
            return rawtime > other.rawtime;
        }
    };

    class KeyInput{
    public:
        Interface(void start())
        Interface(bool getKeyEvevnt(KeyEvent &event))
        Interface(void end())
    };

    class QueryKeyInput:public KeyInput {
    public:

        /*virtual void start() {
            output = true;
            if (outputNext()) {
                DebugI("start")
            }
        }

        virtual void end() {
            output = false;
            if (outputNext()) {
                DebugI("end")
            }
        }

        bool getKeyEvevnt(KeyEvent &event) {
            if (outputNext()) {
                event = events.back();
                events.erase(events.end() - 1);
                Debug("read one input event");
                DebugI("key: " << event.key << " time: " << event.rawtime << " type: " << event.type)
                return true;
            } else {
                return false;
            }
        }*/

        virtual void start() {
            output = true;
        }

        bool getKeyEvevnt(KeyEvent &event) {
            if (outputNext()) {
                event = events.back();
                events.erase(events.end() - 1);
                return true;
            } else {
                return false;
            }
        }

        virtual void end() {
            output = false;
        }

        virtual bool outputNext() {
            return events.size() > 0;
        }



        void sortByTime() {
            sort(events.begin(), events.end());
        }

        vector<KeyEvent> &Events(){
            return events;
        }

    protected:
        vector<KeyEvent> events;
        bool output;
    };

    class KeyOutput{
    public:
        Interface(bool keyDown(int key, const string &txt))
        Interface(bool keyUp(int key, const string &txt))
    };

    class KeyPipe : public QueryKeyInput,public KeyOutput {
    public:
        bool keyDown(int key, const string &txt){
            if (!Timer->isRunning()) {
                return false;
            }
            if (output) {
                return false;
            } else {
                double time = Timer->getTime();
                events.push_back(KeyEvent{
                    KeyState::Down,
                    key,
                    txt,
                    time
                });
                return true;
            }
        }

        bool keyUp(int key, const string &txt){
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

        GetSetO(EdpTimer,Timer)

    private:
        EdpTimer *Timer;
    };

#ifdef USING_QT
    class QTKeyPipe : public KeyPipe{
    public:
        void keyPressEvent(QKeyEvent *event){
            keyDown(event->key(), event->text().toStdString());
        }
        void keyReleaseEvent(QKeyEvent *event){
            keyUp(event->key(), event->text().toStdString());
        }
    };
#endif

    class KeyHolder{
    public:
        virtual void acceptDownEvent(){
            if (!KeyState::isPressed(State)) {
                State |= KeyState::Down;
                State |= KeyState::Pressed;
            }
        }

        void acceptUpEvent() {
            if (KeyState::isPressed(State)) {
                cancel = true;
                State |= KeyState::Up;
            }
        }

        int parseMainState(){
            return State & KeyState::MainStateMask;
        }

        //消耗掉事件停止继续的操作
        virtual void consumeEvent(){
            KeyState::clearState(State, KeyState::Down | KeyState::Up);
        }

        //一帧结束将没有处理掉的事件删除掉
        virtual void pass() {
            if (cancel) {
                cancel = false;
                State = 0;
            }
        }

        GetSet(string,Name)
        GetSet(double,Time)
        GetSet(unsigned int,State)

        bool isPressed() {
            return KeyState::isPressed(State);
        }

    protected:
        double Time;
        string Name;
        unsigned int State;
        bool cancel;
    };

    class KeyFrame{
    public:
        KeyFrame(KeyInput *in) : input(in) {

        }

        explicit KeyFrame() {

        }

        void update(double time) {
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

        void endFrame() {
            ForEach(holders,it,it->second->pass(),map<int,KeyHolder*>::iterator)
        }

        void registerHolder(int key, KeyHolder *holder) {
            holders[key] = holder;
        }

        Getter(double,FrameTime)
        void setKeyInput(KeyInput *in){
            input = in;
        }

    protected:
        map<int,KeyHolder*> holders;
        KeyInput *input;

        double FrameTime;
    };

}



#endif //QT_BB_KEYINPUT_H
