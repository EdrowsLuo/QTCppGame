#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#include "MyDraw.h"
class ProgressBar : public MyDraw
{
public:
    ProgressBar(double);
    ProgressBar(){}
    void draw(QPaintEvent *event,QPainter *painter);
    void set(double v) {
        timeSet = v;
    }
private:
    double timeSet;
};

#endif // PROGRESSBAR_H
