#ifndef SQUAREDOWNH_H
#define SQUAREDOWNH_H
#include <MyDraw.h>
class SquareDownH : public MyDraw
{
public:
    SquareDownH(int,double,double,int);
    void draw(QPaintEvent *event,QPainter *painter);
private:
    int trackeNum,judge1;
    double Pos1,Pos2,xq1,xq2,yq1,yq2,xq3,xq4,yq3,yq4;
};

#endif // SQUAREDOWNH_H
