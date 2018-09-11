#ifndef KEYS_H
#define KEYS_H
#include "MyDraw.h"
#include "defext.h"

class Keys : public MyDraw
{
public:
    Keys(int);
    void draw(QPaintEvent *event,QPainter *painter);
    GetSet(bool,Keyjudge)
    GetSet(int,num)
    //GetSet(int,judge)
private:
    int judge,num;
    bool Keyjudge;
};

#endif // KEYS_H
