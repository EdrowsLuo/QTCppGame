#ifndef CALSCORE_H
#define CALSCORE_H
#include "MyDraw.h";
namespace funning{
    static QString address[10]={"D:/QT/wj/MyBKG/image/score-0.png",
                                 "D:/QT/wj/MyBKG/image/score-1.png",
                                 "D:/QT/wj/MyBKG/image/score-2.png",
                                 "D:/QT/wj/MyBKG/image/score-3.png",
                                 "D:/QT/wj/MyBKG/image/score-4.png",
                                 "D:/QT/wj/MyBKG/image/score-5.png",
                                 "D:/QT/wj/MyBKG/image/score-6.png",
                                 "D:/QT/wj/MyBKG/image/score-7.png",
                                 "D:/QT/wj/MyBKG/image/score-8.png",
                                 "D:/QT/wj/MyBKG/image/score-9.png"};

}
class calScore : public MyDraw
{
public:
    calScore(double,int,int);
    void draw(QPaintEvent *event, QPainter *painter);
private:
    double Pos;
    //double x,y;
    int num,t;
};

#endif // CALSCORE_H
