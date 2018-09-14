#ifndef RANKINGPIC_H
#define RANKINGPIC_H
#include "MyDraw.h"
#include "QString"
#include <string>
using namespace std;
class Rankingpic : MyDraw
{
public:
    Rankingpic(double,double,string);
    Rankingpic(){
        Aaddress = new QString[6];
        ForI(i,0,6){
            MakeString(s,"assets\\image\\ranking-" << i << ".png")
            Aaddress[i]= Project::fromRoot(s).c_str();
        }
    }
    void draw(QPaintEvent *event, QPainter *painter);
    void set(double a,double b,string c)
    {
        rank =c;
        Pos = a;
        Pos2 = b;
    }

private:
    QString *Aaddress;
    string rank;
    double Pos;
    double Pos2;
    //int k;
};

#endif // RANKINGPIC_H

