#include "progressbar.h"
ProgressBar::ProgressBar(double a)
{
    timeSet=a;
}

void ProgressBar::draw(QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path0;
    QPainterPath path1;
    if (timeSet<=1){
        path0.moveTo(0,496);
        path0.lineTo(480*timeSet,496-446*timeSet);
        path0.lineTo(480*timeSet,442-407*timeSet);//*timeSet
        path0.lineTo(0,442);
        path1.moveTo(1280,496);
        path1.lineTo(1280-480*timeSet,496-446*timeSet);
        path1.lineTo(1280-480*timeSet,442-407*timeSet);
        path1.lineTo(1280,442);
    }
    else {
        path0.moveTo(0,496);
        path0.lineTo(480,50);
        path0.lineTo(480,35);
        path0.lineTo(0,442);
        path1.moveTo(1280,496);
        path1.lineTo(800,50);
        path1.lineTo(800,35);
        path1.lineTo(1280,442);
    }
    QLinearGradient linearGradient1(0,469,480,42.5);
    linearGradient1.setColorAt(0,QColor(255,255,255,200));
    linearGradient1.setColorAt(1,QColor(255,255,255,125));
    painter->setPen(QColor(0,238,0,0));
    painter->setBrush(linearGradient1);
    painter->drawPath(path0);
    QLinearGradient linearGradient2(1280,469,800,42.5);
    linearGradient2.setColorAt(0,QColor(255,255,255,200));
    linearGradient2.setColorAt(1,QColor(255,255,255,125));
    painter->setBrush(linearGradient2);
    painter->drawPath(path1);
}
