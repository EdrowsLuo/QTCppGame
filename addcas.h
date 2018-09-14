#ifndef ADDCAS_H
#define ADDCAS_H
#include "MyDraw.h"
#include <QString>
class AddCAS : public MyDraw
{
public:
    AddCAS(double,double,double,double,int);
    void draw(QPaintEvent *event, QPainter *painter);
private:
    QString address1,address2,address3;
    double x,y,w,h;
    int num;
};

#endif // ADDCAS_H
