#ifndef KEYS_H
#define KEYS_H
#include "MyDraw.h"
#include "defext.h"

class Keys : public MyDraw
{
public:
    Keys();
    void draw(QPaintEvent *event,QPainter *painter);
    GetSet(bool,Keyjudge)
    GetSet(int,num)
private:
    int judge,num;
    bool Keyjudge;
};

#endif // KEYS_H
