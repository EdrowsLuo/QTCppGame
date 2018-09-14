#ifndef JUDGESCORE2_H
#define JUDGESCORE2_H
#include <MyDraw.h>
#include <QString>
#include <string>
class judgeScore2 : public MyDraw
{
public:
    judgeScore2(double,double,double,double,int);
    judgeScore2(){
        scorej = new QString[6];
        ForI(i,0,6){
            MakeString(s,"assets\\image\\mania-hit" << i << ".png")
            scorej[i]= Project::fromRoot(s).c_str();
        }
    }
    void draw(QPaintEvent *event, QPainter *painter);
    //void get(double,double,double,double,int);
    void set(double a,double b,double c,double d,int e)
    {
        x=a;
        y=b;
        w=c;
        h=d;
        judge=e;
    }

private:
    int judge;
    bool isBig;
    QString *scorej;
    double x,y,w,h;
};

#endif // JUDGESCORE2_H
