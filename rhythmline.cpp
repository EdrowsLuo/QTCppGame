#include "rhythmline.h"
#include "MyDraw.h"
rhythmLine::rhythmLine(double a)
{
    Pos1=a;
}

void rhythmLine::draw(QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    painter->restore();
}
