#include "background.h"

BackGround::BackGround()
{
}
void BackGround::draw (QPaintEvent *event, QPainter *painter){
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    QPainterPath pathq;
    pathq.moveTo(0,0);
    pathq.lineTo(0,720);
    pathq.lineTo(1280,720);
    pathq.lineTo(1280,0);
    pathq.lineTo(0,0);
    painter->setBrush(QColor(100,100,100));
    painter->drawPath(pathq);
    QPainterPath path;
    path.moveTo(0,528);
    path.lineTo(480,60);
    path.lineTo(480,84);
    path.lineTo(0,612);
    path.lineTo(0,528);
    /*QLinearGradient linearGradient(0,470,300,60);
    linearGradient.setColorAt(0,QColor(0,0,0));
    linearGradient.setColorAt(0.2,QColor(255,255,255));
    linearGradient.setColorAt(0.4,QColor(0,0,0));
    linearGradient.setColorAt(0.6,QColor(255,255,255));
    linearGradient.setColorAt(0.8,QColor(0,0,0));
    linearGradient.setColorAt(1,QColor(255,255,255));*/
    painter->setPen(QColor(0,0,0));
    painter->setBrush(Qt::black);
    painter->drawPath(path);;


    QPainterPath path2;
    path2.moveTo(1280,528);
    path2.lineTo(800,60);
    path2.lineTo(800,84);
    path2.lineTo(1280,612);
    path2.lineTo(1280,528);
    /*QLinearGradient linearGradient2(800,470,500,60);
    linearGradient2.setColorAt(0,QColor(0,0,0));
    linearGradient2.setColorAt(0.2,QColor(255,255,255));
    linearGradient2.setColorAt(0.4,QColor(0,0,0));
    linearGradient2.setColorAt(0.6,QColor(255,255,255));
    linearGradient2.setColorAt(0.8,QColor(0,0,0));
    linearGradient2.setColorAt(1,QColor(255,255,255));*/
    painter->setPen(QColor(0,0,0));
    painter->setBrush(Qt::black);
    painter->drawPath(path2);;


    QPainterPath path3;
    path3.moveTo(0,288);
    path3.lineTo(496,0);
    path3.lineTo(512,0);
    path3.lineTo(0,408);
    path3.lineTo(0,288);
    /*QLinearGradient linearGradient3(0,290,315,0);
    linearGradient3.setColorAt(0,QColor(0,0,0));
    linearGradient3.setColorAt(0.2,QColor(255,255,255));
    linearGradient3.setColorAt(0.4,QColor(0,0,0));
    linearGradient3.setColorAt(0.6,QColor(255,255,255));
    linearGradient3.setColorAt(0.8,QColor(0,0,0));
    linearGradient3.setColorAt(1,QColor(255,255,255));*/
    painter->setPen(QColor(0,0,0));
    painter->setBrush(Qt::black);
    painter->drawPath(path3);

    QPainterPath path4;
    path4.moveTo(1280,288);
    path4.lineTo(784,0);
    path4.lineTo(768,0);
    path4.lineTo(1280,408);
    path4.lineTo(1280,288);
    /*QLinearGradient linearGradient4(800,290,485,0);
    linearGradient4.setColorAt(0,QColor(0,0,0));
    linearGradient4.setColorAt(0.2,QColor(255,255,255));
    linearGradient4.setColorAt(0.4,QColor(0,0,0));
    linearGradient4.setColorAt(0.6,QColor(255,255,255));
    linearGradient4.setColorAt(0.8,QColor(0,0,0));
    linearGradient4.setColorAt(1,QColor(255,255,255));*/
    painter->setPen(QColor(0,0,0));
    painter->setBrush(Qt::black);
    painter->drawPath(path4);

    QPainterPath path5;
    path5.moveTo(0,612);
    path5.lineTo(1280,612);
    path5.lineTo(1280,660);
    path5.lineTo(0,660);
    path5.moveTo(0,684);
    path5.lineTo(1280,684);
    path5.lineTo(1280,720);
    path5.lineTo(0,720);
    painter->setPen(QColor(255,0,0));
    painter->setBrush(QColor(255,0,0));
    painter->drawPath(path5);
    //painter->setPen(Qt::white);
    //painter->drawLine(800,540,0,540);
    QPainterPath path6;
    path6.moveTo(0,660);
    path6.lineTo(1280,660);
    path6.lineTo(1280,684);
    path6.lineTo(0,684);
    painter->setPen(QColor(130,0,0));
    painter->setBrush(QColor(130,0,0));
    painter->drawPath(path6);
    painter->setPen(Qt::white);
    painter->drawLine(1280,660,0,660);
    painter->restore();
}
