#include "squaredownh.h"
#include "coordinate.h"
SquareDownH::SquareDownH(int a,double b,double c,int d)
{
    trackeNum=a;
    Pos1=b;
    Pos2=c;
    judge1=d;
}
void SquareDownH::draw (QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path1;
    coordinate coord1(judge1);
    coord1.calculateSize1(trackeNum,Pos1);
    xq1=coord1.setoutx1();
    xq2=coord1.setoutx2();
    yq1=coord1.setouty1();
    yq2=coord1.setouty2();
    coordinate coord2(judge1);
    coord2.calculateSize1(trackeNum,Pos2);
    xq3=coord2.setoutx1();
    xq4=coord2.setoutx2();
    yq3=coord2.setouty1();
    yq4=coord2.setouty2();
    path1.moveTo(xq1,yq1);
    path1.lineTo(xq2,yq2);
    path1.lineTo(xq4,yq4);
    path1.lineTo(xq3,yq3);
    path1.lineTo(xq1,yq1);
    painter->setPen(QColor(255,215,000));
    painter->setBrush(Qt::black);
    painter->drawPath(path1);
}