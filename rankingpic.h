#ifndef RANKINGPIC_H
#define RANKINGPIC_H
#include "MyDraw.h"
#include "QString"
#include <string>
using namespace std;
class Rankingpic : MyDraw
{
public:
    Rankingpic(double,string);
    void draw(QPaintEvent *event, QPainter *painter);
private:
    QString *Aaddress;
    string rank;
    double Pos;
    //int k;
};

#endif // RANKINGPIC_H

