#ifndef RHYTHMLINE_H
#define RHYTHMLINE_H
#include "MyDraw.h"
class rhythmLine : public MyDraw
{
public:
    rhythmLine(double);
    void draw(QPaintEvent *event, QPainter *painter);
private:
    double Pos1;
};

#endif // RHYTHMLINE_H
