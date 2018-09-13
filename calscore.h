#ifndef CALSCORE_H
#define CALSCORE_H
#include "MyDraw.h";
#include <string>

class calScore : public MyDraw
{
public:
    calScore(double,int,int);
    void draw(QPaintEvent *event, QPainter *painter);
private:
    double Pos;
    //double x,y;
    int num,t;
    std::string *address;
};

#endif // CALSCORE_H
