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
    if (rank == Mania::Ranking_C) {
        pixmap1.load(Aaddress[1]);
    } else if (rank == Mania::Ranking_B) {
        pixmap1.load(Aaddress[2]);
    } else if (rank == Mania::Ranking_A) {
        pixmap1.load(Aaddress[3]);
    } else if (rank == Mania::Ranking_S) {
        pixmap1.load(Aaddress[4]);
    } else if (rank == Mania::Ranking_SS) {
        pixmap1.load(Aaddress[5]);
    } else {
        pixmap1.load(Aaddress[0]);
    }
    painter->drawPixmap(500+200*(2-Pos2),320-250*Pos,400*Pos2,500*Pos,pixmap1);
    painter->restore();
}

void Pressesc::draw(QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing,true);
    QPixmap pixmap1;
    pixmap1.load(AAaddress);
    painter->setOpacity(tran);
    painter->drawPixmap(0,0,505,40,pixmap1);
    painter->restore();
}
