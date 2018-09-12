#include "tracke.h"

trackE::trackE(int a)
{
    judge=a;
}
void trackE::draw (QPaintEvent *event, QPainter *painter){
    painter->save();
    QPainterPath path;
    //judge=0;
    painter->setRenderHint(QPainter::Antialiasing, true);
    QLinearGradient linearGradient1(640,720,640,0);
    linearGradient1.setColorAt(0,QColor(40,44,53,255));
    linearGradient1.setColorAt(1,QColor(40,44,53,150));
    painter->setPen(QColor(255,215,000));
    path.moveTo(0,612);
    path.lineTo(480,84);
    path.lineTo(800,84);
    path.lineTo(1280,612);
    painter->setBrush(linearGradient1);
    painter->drawPath(path);

    painter->setPen(QColor(255,215,000));
    painter->drawLine(480,84,800,84);
    if (judge==1)
    {
        painter->drawLine(320,612,560,84);
        painter->drawLine(640,612,640,84);
        painter->drawLine(960,612,720,84);

    }
    if (judge==0)
    {
        painter->drawLine(183,612,526,84);
        painter->drawLine(366,612,572,84);
        painter->drawLine(548,612,617,84);
        painter->drawLine(731,612,663,84);
        painter->drawLine(914,612,709,84);
        painter->drawLine(1097,612,755,84);
        painter->drawLine(1280,612,800,84);
    }
    QPainterPath path1;
    path1.moveTo(0,612);
    path1.lineTo(48,559.2);
    path1.lineTo(1232,559.2);
    path1.lineTo(1280,612);
    path1.lineTo(0,612);
    painter->setPen(QColor(3,99,141));
    painter->setBrush(QColor(3,99,141,150));//
    painter->drawPath(path1);

    painter->restore();
}
