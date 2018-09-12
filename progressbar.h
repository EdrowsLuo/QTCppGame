#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#include "MyDraw.h"
class ProgressBar : public MyDraw
{
public:
    ProgressBar(double);
    void draw(QPaintEvent *event,QPainter *painter);
private:
    double timeSet;
};

#endif // PROGRESSBAR_H
