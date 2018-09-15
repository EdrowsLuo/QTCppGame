#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "MyDraw.h"
#include <QString>
#include <string>

class BackGround: public MyDraw
{
public:
    BackGround();
    void draw(QPaintEvent *event,QPainter *painter);
    void set(std::string p){
        address = p.c_str();
    }

private:
    double height1,height2,length1,length2;
    QString address;
};

#endif // BACKGROUND_H
