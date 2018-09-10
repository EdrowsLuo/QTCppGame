#include "drawtext.h"
#include <QPixmap>
DrawTextW::DrawTextW(int a,int b,int c,int d,int f)
{
    x=a;
    y=b;
    w=c;
    h=d;
    num=f;

}
void DrawTextW::draw(QPaintEvent *event,QPainter *painter){

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPixmap Pixmap1;
    Pixmap1.load(kidding::Paddress[num]);
    painter->drawPixmap(x,y,w,h,Pixmap1);
    painter->restore();
}
