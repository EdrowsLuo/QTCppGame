#include "judgescore2.h"
#include <sstream>
#include "Project.h"
judgeScore2::judgeScore2(double a,double b,double c,double d,int e)
{
    x=a;
    y=b;
    w=c;
    h=d;
    judge=e;
    scorej = new QString[6];
    ForI(i,0,6){
        MakeString(s,"assets\\image\\mania-hit" << i << ".png")
        scorej[i]= Project::fromRoot(s).c_str();
    }
}

/*void judgeScore2::get(double a, double b, double c, double d, int e){
    x=a;
    y=b;
    w=c;
    h=d;
    judge=e;
}*/

void judgeScore2::draw(QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPixmap Pixmap1;
    Pixmap1.load(scorej[judge]);
    painter->drawPixmap(x,y,w,h,Pixmap1);
    painter->restore();
}
