#include "shadow.h"
Shadow::Shadow()
{
}

void Shadow::draw(QPaintEvent *event, QPainter *painter){
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path6;
    path6.moveTo(0,612);
    path6.lineTo(480,84);
    path6.lineTo(486,84);
    path6.lineTo(35,612);
    path6.lineTo(0,612);
    QLinearGradient linearGradient3(240,348,260.8,366);
    linearGradient3.setColorAt(0,QColor(20,20,20,200));
    linearGradient3.setColorAt(1,QColor(20,20,20,0));
    painter->setPen(QColor(0,0,0,0));
    painter->setBrush(linearGradient3);
    painter->drawPath(path6);
    QPainterPath path7;
    path7.moveTo(1280,612);
    path7.lineTo(800,84);
    path7.lineTo(794,84);
    path7.lineTo(1245,612);
    path7.lineTo(0,612);
    QLinearGradient linearGradient4(1040,348,1019.2,366);
    linearGradient4.setColorAt(0,QColor(20,20,20,200));
    linearGradient4.setColorAt(1,QColor(20,20,20,0));
    painter->setPen(QColor(0,0,0,0));
    painter->setBrush(linearGradient4);
    painter->drawPath(path7);
    painter->restore();
}
