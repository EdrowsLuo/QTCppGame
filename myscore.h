#ifndef MYSCORE_H
#define MYSCORE_H
#include "MyDraw.h"

class MyScore :public MyDraw
{
public:
    MyScore(int,int,int,int,int);

    MyScore() {
        Paddress = new QString[10];
        ForI(i, 0, 10) {
            MakeString(s, "assets\\image\\score-" << i << ".png")
            Paddress[i] = Project::fromRoot(s).c_str();
        }
    }

    void draw(QPaintEvent *event,QPainter *painter);
    void set(int a,int b,int c,int d,int f)
    {
        x=a;
        y=b;
        w=c;
        h=d;
        num=f;
    }
private:
    QString *Paddress;
    int num;
    int x,y,w,h;
};


#endif //
