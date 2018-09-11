#ifndef MYSCORE_H
#define MYSCORE_H
#include "MyDraw.h"
namespace kidding{
    static QString Paddress[10]={"D:/QT/wj/MyBKG/image/score-0.png",
                                 "D:/QT/wj/MyBKG/image/score-1.png",
                                 "D:/QT/wj/MyBKG/image/score-2.png",
                                 "D:/QT/wj/MyBKG/image/score-3.png",
                                 "D:/QT/wj/MyBKG/image/score-4.png",
                                 "D:/QT/wj/MyBKG/image/score-5.png",
                                 "D:/QT/wj/MyBKG/image/score-6.png",
                                 "D:/QT/wj/MyBKG/image/score-7.png",
                                 "D:/QT/wj/MyBKG/image/score-8.png",
                                 "D:/QT/wj/MyBKG/image/score-9.png"};

}
class MyScore :public MyDraw
{
public:
    MyScore(int,int,int,int,int);
    void draw(QPaintEvent *event,QPainter *painter);

private:

    int num;
    int x,y,w,h;
};


#endif //
