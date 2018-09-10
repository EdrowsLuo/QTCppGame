#include "keys.h"

Keys::Keys()
{
}

void Keys::draw(QPaintEvent *event,QPainter *painter){
    num=0;
    judge=1;
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    //painter->drawLine(0,0,1280,720);
   QPainterPath path;
   path.moveTo(0,612);
   path.lineTo(48,559.2);
   path.lineTo(1232,559.2);
   path.lineTo(1280,612);
   path.lineTo(0,612);
   painter->setPen(QColor(255,215,000));
   painter->setBrush(QColor(225,200,0));
   painter->drawPath(path);
   QPainterPath pathway[4];
   QLinearGradient linearGradient1(640,720,640,0);
   linearGradient1.setColorAt(0,QColor(255,255,255,150));
   linearGradient1.setColorAt(1,QColor(255,255,255,255));
   if (judge==1){

           if (Keyjudge){
               pathway[num].moveTo(320*num,612);
               pathway[num].lineTo(480+80*num,84);
               pathway[num].lineTo(560+80*num,84);
               pathway[num].lineTo(320+320*num,612);
               pathway[num].lineTo(320*num,612);
               painter->setBrush(linearGradient1);
               painter->drawPath(pathway[num]);
           }

   }
   painter->restore();
}
