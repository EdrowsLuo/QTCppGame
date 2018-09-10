#ifndef TRACKE_H
#define TRACKE_H
#include "MyDraw.h"

class trackE : public MyDraw
{
public:
    trackE(int);
    void draw(QPaintEvent *event,QPainter *painter);
    int judge;
};

#endif // TRACKE_H
