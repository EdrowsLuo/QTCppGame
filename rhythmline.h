#ifndef RHYTHMLINE_H
#define RHYTHMLINE_H
#include "MyDraw.h"
class rhythmLine : public MyDraw
{
public:
    rhythmLine(double);
    rhythmLine(){}
    void draw(QPaintEvent *event, QPainter *painter);
    void set(double a)
    {
        Pos1=a;
    }
private:
    double Pos1;
};

#endif // RHYTHMLINE_H
