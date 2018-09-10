#ifndef TRACKE_H
#define TRACKE_H
#include "MyDraw.h"
#include "defext.h"
class trackE : public MyDraw
{
public:
    trackE(int);
    void draw(QPaintEvent *event,QPainter *painter);
    //GetSet(int,judge)
private:
    int judge;
};

#endif // TRACKE_H
