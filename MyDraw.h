#ifndef MYDRAW_H
#define MYDRAW_H

#include <QPainter>
#include <QWidget>
#include <QPaintEvent>
#include <QString>

class MyDraw{
public:
    virtual void draw(QPaintEvent *event,QPainter *painter)=0;
    QPainterPath path;
    //QLinearGradient linearGradient(int,int,int,int);
};


#endif // MYDRAW_H
