#include "myscore.h"
#include <QPixmap>
MyScore::MyScore(int a,int b,int c,int d,int f)
{
    x=a;
    y=b;
    w=c;
    h=d;
    num=f;

}
void MyScore::draw(QPaintEvent *event,QPainter *painter){

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPixmap Pixmap1;
    Pixmap1.load(kidding::Paddress[num]);
    painter->drawPixmap(x,y,w,h,Pixmap1);
    painter->restore();
}
