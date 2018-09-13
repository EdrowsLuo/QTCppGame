#include "myscore.h"
#include <QPixmap>
#include "defext.h"
#include "Project.h"
#include <sstream>

using namespace nso;

MyScore::MyScore(int a,int b,int c,int d,int f)
{
    x=a;
    y=b;
    w=c;
    h=d;
    num=f;
    Paddress = new QString[10];
    ForI(i,0,10){
        MakeString(s,"assets\\image\\score-" << i << ".png")
        Paddress[i]= Project::fromRoot(s).c_str();
    }
}
void MyScore::draw(QPaintEvent *event,QPainter *painter){

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPixmap Pixmap1;
    Pixmap1.load(Paddress[num]);
    painter->drawPixmap(x,y,w,h,Pixmap1);
    painter->restore();
}
