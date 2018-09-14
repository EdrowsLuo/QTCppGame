#ifndef JUDGESCORE_H
#define JUDGESCORE_H
#include "MyDraw.h"
#include <QString>
#include <string>
/*namespace picpic{
    static QString scorej[6]={
        "D:\\QT\\wj\\MyBKG\\image\\mania-hit0.png",
        "D:\\QT\\wj\\MyBKG\\image\\mania-hit50.png",
        "D:\\QT\\wj\\MyBKG\\image\\mania-hit100.png",
        "D:\\QT\\wj\\MyBKG\\image\\mania-hit200.png",
        "D:\\QT\\wj\\MyBKG\\image\\mania-hit300.png",
        "D:\\QT\\wj\\MyBKG\\image\\mania-hit300g.png"
    };*/

class judgeScore : public MyDraw
{
public:
    judgeScore(int,bool);
    judgeScore(){
        scorej = new QString[6];
        ForI(i,0,6){
            MakeString(s,"assets\\image\\mania-hit" << i << ".png")
            scorej[i]= Project::fromRoot(s).c_str();
        }
    }
    void draw(QPaintEvent *event, QPainter *painter);
    void set(int a,bool b)
    {
        judge=a;
        isBig=b;
    }

private:
    int judge;
    bool isBig;
    QString *scorej;
};

#endif // JUDGESCORE_H
