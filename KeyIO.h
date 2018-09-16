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

        static bool isPressed(unsigned int stat);

        static void clearState(unsigned int &state, unsigned int code);

    };

    class KeyEvent{
    public:
        int type;
        int key;
        string text;
        double rawtime;

        bool operator<(const KeyEvent &other) const;
    };

    class KeyInput{
    public:
        Interface(void start())
        Interface(bool getKeyEvevnt(KeyEvent &event))
        Interface(void end())
    };

    class QueryKeyInput:public KeyInput {
    public:

        virtual void start();

        bool getKeyEvevnt(KeyEvent &event);

        virtual void end();

        virtual bool outputNext();

        void sortByTime();

        vector<KeyEvent> &Events();

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
        bool keyDown(int key, const string &txt);

        bool keyUp(int key, const string &txt);

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
        virtual void acceptDownEvent();

        void acceptUpEvent();

        int parseMainState();

        //消耗掉事件停止继续的操作
        virtual void consumeEvent();

        //一帧结束将没有处理掉的事件删除掉
        virtual void pass();

        GetSet(string,Name)
        GetSet(double,Time)
        GetSet(unsigned int,State)

        bool isPressed();

    protected:
        double Time;
        string Name;
        unsigned int State;
        bool cancel;
    };

    class KeyFrame{
    public:
        explicit KeyFrame(KeyInput *in);

        explicit KeyFrame();

        void update(double time);

        void endFrame();

        void registerHolder(int key, KeyHolder *holder);

        Getter(double,FrameTime)
        void setKeyInput(KeyInput *in);

    protected:
        map<int,KeyHolder*> holders;
        KeyInput *input;

        double FrameTime;
    };

}



#endif //QT_BB_KEYINPUT_H
