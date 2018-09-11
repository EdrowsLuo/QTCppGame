#ifndef SQUAREDOWN_H
#define SQUAREDOWN_H
#include <MyDraw.h>
#include <coordinate.h>
class SquareDown:public MyDraw
{
public:
    SquareDown(int,double,int);
    void draw(QPaintEvent *event,QPainter *painter);
private:
    int trackeNum,judge1;
    double Pos2,xq1,xq2,yq1,yq2,xq3,xq4,yq3,yq4;
};

#endif // SQUAREDOWN_H
