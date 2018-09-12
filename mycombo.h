#ifndef MYCOMBO_H
#define MYCOMBO_H
#include "MyDraw.h"
#include <QString>
namespace YOUKY{
    static QString FCombo[10]{
        "D:/QT/wj/MyBKG/image/score-0.png",
        "D:/QT/wj/MyBKG/image/score-1.png",
        "D:/QT/wj/MyBKG/image/score-2.png",
        "D:/QT/wj/MyBKG/image/score-3.png",
        "D:/QT/wj/MyBKG/image/score-4.png",
        "D:/QT/wj/MyBKG/image/score-5.png",
        "D:/QT/wj/MyBKG/image/score-6.png",
        "D:/QT/wj/MyBKG/image/score-7.png",
        "D:/QT/wj/MyBKG/image/score-8.png",
        "D:/QT/wj/MyBKG/image/score-9.png"};
    static QString RCombo[10]{
        "D:\\QT\\wj\\MyBKG\\image\\combo-0@2x.png",
        "D:\\QT\\wj\\MyBKG\\image\\combo-1@2x.png",
        "D:\\QT\\wj\\MyBKG\\image\\combo-2@2x.png",
        "D:\\QT\\wj\\MyBKG\\image\\combo-3@2x.png",
        "D:\\QT\\wj\\MyBKG\\image\\combo-4@2x.png",
        "D:\\QT\\wj\\MyBKG\\image\\combo-5@2x.png",
        "D:\\QT\\wj\\MyBKG\\image\\combo-6@2x.png",
        "D:\\QT\\wj\\MyBKG\\image\\combo-7@2x.png",
        "D:\\QT\\wj\\MyBKG\\image\\combo-8@2x.png",
        "D:\\QT\\wj\\MyBKG\\image\\combo-9@2x.png"};
}
class MyCombo : public MyDraw
{
public:
    MyCombo(int,bool);
    void draw(QPaintEvent *event,QPainter *painter);
private:
    int num;
    QString mark1;
    bool isBig;
};

#endif // MYCOMBO_H
