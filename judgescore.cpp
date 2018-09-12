#include "judgescore.h"

judgeScore::judgeScore(int a,bool b)
{
    judge=a;
    isBig=b;
}

void judgeScore::draw(QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPixmap pixmap1;
    pixmap1.load(picpic::scorej[judge]);
    if(isBig){
        painter->drawPixmap(544,612,192,108,pixmap1);
    }
    else {
    painter->drawPixmap(560,612,160,90,pixmap1);
    }
    painter->restore();
}

