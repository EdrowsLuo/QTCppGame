#include "calscore.h"

calScore::calScore(double a,int b,int c)
{
    Pos=a;
    num=b;
    t=c;
}

void calScore::draw(QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPixmap pixmapnum;
    //pixmapnum.load(address[num]);
    painter->drawPixmap(514+36*t,612-32*Pos,36,64*Pos,pixmapnum);
    painter->restore();
}
