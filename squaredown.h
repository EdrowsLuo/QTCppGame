#ifndef SQUAREDOWN_H
#define SQUAREDOWN_H
#include <MyDraw.h>
#include <coordinate.h>
class SquareDown:public MyDraw
{
public:
    SquareDown(int,double,int);
    SquareDown(){}
    void draw(QPaintEvent *event,QPainter *painter);
    void set(int a,double b,int c)
    {
        trackeNum=a;
        Pos2=b;
        judge1=c;
    }
private:
    int trackeNum,judge1;
    double Pos2,xq1,xq2,yq1,yq2,xq3,xq4,yq3,yq4;
};

#endif // SQUAREDOWN_H
