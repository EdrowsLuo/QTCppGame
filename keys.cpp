#include "keys.h"

Keys::Keys(int a)
{
    judge=a;
}

void Keys::draw(QPaintEvent *event,QPainter *painter){
    //num=0;
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    //painter->drawLine(0,0,1280,720);
    painter->setPen(QColor(255,215,000,0));
   QPainterPath pathway[4];
   QPainterPath pathway1[7];
   QLinearGradient linearGradient1(640,720,640,0);
   linearGradient1.setColorAt(0,QColor(230,230,230,60));
   linearGradient1.setColorAt(1,QColor(230,230,230,120));
   if (judge==1){

           if (Keyjudge){
               pathway[num].moveTo(320*num,612);
               pathway[num].lineTo(480+80*num,84);
               pathway[num].lineTo(560+80*num,84);
               pathway[num].lineTo(320+320*num,612);
               pathway[num].lineTo(320+320*num,720);
               pathway[num].lineTo(320*num,720);
               pathway[num].lineTo(320*num,612);
               painter->setBrush(linearGradient1);
               painter->drawPath(pathway[num]);
           }

   }
   if (judge==0){
       if (Keyjudge){
           pathway1[num].moveTo(1280/7*num,612);
           pathway1[num].lineTo(480+320/7*num,84);
           pathway1[num].lineTo(480+320/7*(num+1),84);
           pathway1[num].lineTo(1280/7*(num+1),612);
           pathway1[num].lineTo(1280/7*num,612);
           painter->setBrush(linearGradient1);
           painter->drawPath(pathway1[num]);
       }
   }

   painter->restore();
}
