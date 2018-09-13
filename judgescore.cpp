#include "judgescore.h"
#include <sstream>
#include "Project.h"
judgeScore::judgeScore(int a,bool b)
{
    judge=a;
    isBig=b;
    scorej = new QString[6];
    ForI(i,0,6){
        MakeString(s,"assets\\image\\mania-hit" << i << ".png")
        scorej[i]= Project::fromRoot(s).c_str();
    }
}

void judgeScore::draw(QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPixmap pixmap1;
    pixmap1.load(scorej[judge]);
    if(isBig){
        painter->drawPixmap(544,612,192,108,pixmap1);
    }
    else {
    painter->drawPixmap(560,612,160,90,pixmap1);
    }
    painter->restore();
}

