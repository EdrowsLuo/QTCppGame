#include "rhythmline.h"
#include "MyDraw.h"
rhythmLine::rhythmLine(double a)
{
    Pos1=a;
}

void rhythmLine::draw(QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QColor(255,215,000));
    //painter->drawLine(480*Pos1,288-480*Pos1/496*288,480*Pos1,612-528*Pos1);
    painter->drawLine(480*Pos1,612-528*Pos1,1280-480*Pos1,612-528*Pos1);
    //painter->drawLine(1280-480*Pos1,288-480*Pos1/496*288,1280-480*Pos1,612-528*Pos1);
    painter->restore();
}
