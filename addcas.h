#ifndef ADDCAS_H
#define ADDCAS_H
#include "MyDraw.h"
#include <QString>
class AddCAS : public MyDraw
{
public:
    AddCAS(double,double,double,double,int);
    AddCAS(){
        address1 = Project::fromRoot("assets\\image\\Combo.png").c_str();
        address2 = Project::fromRoot("assets\\image\\Accuracy.png").c_str();
        address3 = Project::fromRoot("assets\\image\\Score.png").c_str();
    }
    void draw(QPaintEvent *event, QPainter *painter);
    void set(double a,double b,double c,double d,int e)
    {
        x=a;
        y=b;
        w=c;
        h=d;
        num=e;
    }
private:
    QString address1,address2,address3;
    double x,y,w,h;
    int num;
};

#endif // ADDCAS_H
