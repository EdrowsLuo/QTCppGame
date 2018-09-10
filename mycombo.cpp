#include "mycombo.h"
#include <cstring>
#include <stdio.h>

MyCombo::MyCombo()
{
}
void MyCombo::draw (QPaintEvent *event, QPainter *painter){
    num=1000;
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPen pen1;
    QString mark1=QString::number(num);
    QPainterPath path1;
    QFont MyFont1;
    MyFont1.setFamily("cousols");
    MyFont1.setPointSize(90);
    //MyFont1.setItalic(true);
    if (num<100){
        pen1.setWidth(2);
        painter->setPen(pen1);
        QLinearGradient linearGradient3(50,0,50,100);
        linearGradient3.setColorAt(0,QColor(0,134,139));
        linearGradient3.setColorAt(1,QColor(0,229,238));
        //linearGradient3.setColorAt(1,QColor(224,255,255));
        painter->setBrush(linearGradient3);
    }
    else {
        pen1.setWidth(0);
        painter->setPen(pen1);
        MyFont1.setPointSize(95);
        QLinearGradient linearGradient2(50,0,50,100);
        linearGradient2.setColorAt(0,QColor(205,173,0));
        linearGradient2.setColorAt(1,QColor(255,215,0));
        //linearGradient2.setColorAt(1,QColor(255,245,255));
        painter->setBrush(linearGradient2);
        //painter->setBrush(Qt::yellow);
    }
    path1.addText(0,100,MyFont1,mark1);
    painter->setPen(Qt::white);
    painter->drawPath(path1);
    painter->restore();
}
