#include "addcas.h"

AddCAS::AddCAS(double a,double b,double c,double d,int e)
{
    address1 = Project::fromRoot("assets\\image\\Combo.png").c_str();
    address2 = Project::fromRoot("assets\\image\\Accuracy.png").c_str();
    address3 = Project::fromRoot("assets\\image\\Score.png").c_str();
    x=a;
    y=b;
    w=c;
    h=d;
    num=e;
}

void AddCAS::draw(QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    if (num==1){
        QPixmap pixmap;
        pixmap.load(address1);
        painter->drawPixmap(x,y,w,h,pixmap);
    }
    if (num==2){
        QPixmap pixmap;
        pixmap.load(address2);
        painter->drawPixmap(x,y,w,h,pixmap);
    }
    if (num==3){
        QPixmap pixmap;
        pixmap.load(address3);
        painter->drawPixmap(x,y,w,h,pixmap);
    }
    painter->restore();
}


