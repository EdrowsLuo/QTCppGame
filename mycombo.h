#ifndef MYCOMBO_H
#define MYCOMBO_H
#include "MyDraw.h"
#include <QString>
class MyCombo : public MyDraw
{
public:
    MyCombo();
    void draw(QPaintEvent *event,QPainter *painter);
private:
    int num;
    QString mark1;
};

#endif // MYCOMBO_H
