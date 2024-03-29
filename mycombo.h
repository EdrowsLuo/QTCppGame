#ifndef MYCOMBO_H
#define MYCOMBO_H
#include "MyDraw.h"
#include <QString>
/*namespace YOUKY{
    static QString RCombo[10]{
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
    static QString FCombo[10]{
        "D:\\QT\\wj\\MyBKG\\image\\default-0.png",
        "D:\\QT\\wj\\MyBKG\\image\\default-1.png",
        "D:\\QT\\wj\\MyBKG\\image\\default-2.png",
        "D:\\QT\\wj\\MyBKG\\image\\default-3.png",
        "D:\\QT\\wj\\MyBKG\\image\\default-4.png",
        "D:\\QT\\wj\\MyBKG\\image\\default-5.png",
        "D:\\QT\\wj\\MyBKG\\image\\default-6.png",
        "D:\\QT\\wj\\MyBKG\\image\\default-7.png",
        "D:\\QT\\wj\\MyBKG\\image\\default-8.png",
        "D:\\QT\\wj\\MyBKG\\image\\default-9.png"};
}*/
class MyCombo : public MyDraw
{
public:
    MyCombo(int,bool);
    MyCombo(){
        FCombo = new QString[10];
        ForI(i,0,10){
            MakeString(s,"assets\\image\\default-" << i << ".png")
            FCombo[i]= Project::fromRoot(s).c_str();
        }
    }
    void draw(QPaintEvent *event,QPainter *painter);
    void set(int a,bool b)
    {
        num=a;
        isBig=b;     //\\image\\default-0.png
    }
private:
    int num;
    QString mark1;
    bool isBig;
    //QString *RCombo;
    QString *FCombo;
};

#endif // MYCOMBO_H
