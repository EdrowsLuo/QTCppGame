#ifndef RANKINGBG_H
#define RANKINGBG_H
#include "MyDraw.h"
#include <QPixmap>
#include "pixmapmanager.h"
class RankingBG : MyDraw
{
public:
    RankingBG(Pixmapmanager *mm);
    void draw(QPaintEvent *event, QPainter *painter);
    void gettran(double);
private:
    double tran;
    Pixmapmanager *m;
    //QPixmap Pixmap0;
};

#endif // RANKINGBG_H
