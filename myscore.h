#ifndef MYSCORE_H
#define MYSCORE_H
#include "MyDraw.h"

class MyScore :public MyDraw
{
public:
    MyScore(int,int,int,int,int);
    void draw(QPaintEvent *event,QPainter *painter);

private:
    QString *Paddress;
    int num;
    int x,y,w,h;
};


#endif //
