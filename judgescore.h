#ifndef JUDGESCORE_H
#define JUDGESCORE_H
#include "MyDraw.h"
#include <QString>
namespace picpic{
    static QString scorej[6]={
        "D:\\QT\\wj\\MyBKG\\image\\mania-hit0.png",
        "D:\\QT\\wj\\MyBKG\\image\\mania-hit50.png",
        "D:\\QT\\wj\\MyBKG\\image\\mania-hit100.png",
        "D:\\QT\\wj\\MyBKG\\image\\mania-hit200.png",
        "D:\\QT\\wj\\MyBKG\\image\\mania-hit300.png",
        "D:\\QT\\wj\\MyBKG\\image\\mania-hit300g.png"
    };
}
class judgeScore : public MyDraw
{
public:
    judgeScore(int,bool);
    void draw(QPaintEvent *event, QPainter *painter);
private:
    int judge;
    bool isBig;
};

#endif // JUDGESCORE_H
