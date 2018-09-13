#ifndef JUDGESCORE2_H
#define JUDGESCORE2_H
#include <MyDraw.h>
#include <QString>
#include <string>
class judgeScore2 : public MyDraw
{
public:
    judgeScore2(double,double,double,double,int);
    void draw(QPaintEvent *event, QPainter *painter);
    //void get(double,double,double,double,int);

private:
    int judge;
    bool isBig;
    QString *scorej;
    double x,y,w,h;
};

#endif // JUDGESCORE2_H
