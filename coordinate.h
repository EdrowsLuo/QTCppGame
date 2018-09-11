#ifndef COORDINATE_H
#define COORDINATE_H
#include "MyDraw.h"
class coordinate
{
public:
    coordinate(int);
    //void draw(QPaintEvent *event,QPainter *painter);
    void calculateSize1(int,double);
    void calculateSize2(int,double,double);
    double setoutx1();
    double setoutx2();
    double setouty1();
    double setouty2();

private:
    int judge;
    int Num;
    double Pos1,x1,y1,x2,y2;
};

#endif // COORDINATE_H
