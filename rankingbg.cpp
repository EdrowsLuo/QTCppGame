#include "rankingbg.h"

RankingBG::RankingBG(double a)
{
    tran = a;
}

void ge
void RankingBG::draw (QPaintEvent *event, QPainter *painter){
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    QPixmap Pixmap0;
    Pixmap0.load("D:\\QT\\wj\\MyBKG\\image\\ranking-panel.png");
    painter->setOpacity(tran);
    painter->drawPixmap(0,0,1280,720,Pixmap0);
}
