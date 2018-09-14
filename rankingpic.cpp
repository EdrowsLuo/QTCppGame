#include "rankingpic.h"
#include <sstream>
Rankingpic::Rankingpic(double a,double b,string c)
{
    rank =c;
    Pos = a;
    Pos2 = b;
    Aaddress = new QString[6];
    ForI(i,0,6){
        MakeString(s,"assets\\image\\ranking-" << i << ".png")
        Aaddress[i]= Project::fromRoot(s).c_str();
    }
}

void Rankingpic::draw (QPaintEvent *event, QPainter *painter){
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    QPixmap pixmap1;
    if (rank == Mania::Ranking_D){
            pixmap1.load(Aaddress[0]);
        }
        if (rank == Mania::Ranking_C){
            pixmap1.load(Aaddress[1]);
        }
        if (rank == Mania::Ranking_B){
            pixmap1.load(Aaddress[2]);
        }
        if (rank == Mania::Ranking_A){
            pixmap1.load(Aaddress[3]);
        }
        if (rank == Mania::Ranking_S){
            pixmap1.load(Aaddress[4]);
        }
        if (rank == Mania::Ranking_SS){
            pixmap1.load(Aaddress[5]);
        }
        painter->drawPixmap(500+200*(2-Pos2),320-250*Pos,400*Pos2,500*Pos,pixmap1);
        painter->restore();
}
