#ifndef SHADOW_H
#define SHADOW_H
#include "MyDraw.h"
class Shadow : public MyDraw
{
public:
    Shadow();
    void draw(QPaintEvent *event,QPainter *painter);
};

#endif // SHADOW_H
