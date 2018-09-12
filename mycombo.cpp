#include "mycombo.h"
#include <cstring>
#include <stdio.h>

MyCombo::MyCombo(int a,bool b)
{
    num=a;
    isBig=b;
}
void MyCombo::draw (QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    if (num<10){
        QPixmap qpixmap1;
        qpixmap1.load(YOUKY::FCombo[num]);
        if (isBig){
            painter->drawPixmap(622,40,36,60,qpixmap1);
        }
        else {
            painter->drawPixmap(625,40,30,50,qpixmap1);
        }
    }
    if (10<=num&&num<100){
        QPixmap qpixmap2;
        QPixmap qpixmap3;
        int a=num/10;
        int b=num-10*a;
        qpixmap2.load(YOUKY::FCombo[a]);
        qpixmap3.load(YOUKY::FCombo[b]);
        if (isBig){
            painter->drawPixmap(604,45,36,60,qpixmap2);
            painter->drawPixmap(640,45,36,60,qpixmap3);
        }
        else {
            painter->drawPixmap(610,45,30,50,qpixmap2);
            painter->drawPixmap(640,45,30,50,qpixmap3);
        }
    }
    if (100<=num&&num<1000){
        QPixmap qpixmap4,qpixmap5,qpixmap6;
        int c=num/100;
        int d=num/10-c*10;
        int f=num-c*100-d*10;
        qpixmap4.load(YOUKY::FCombo[c]);
        qpixmap5.load(YOUKY::FCombo[d]);
        qpixmap6.load(YOUKY::FCombo[f]);
        if (isBig){
            painter->drawPixmap(586,45,36,60,qpixmap4);
            painter->drawPixmap(622,45,36,60,qpixmap5);
            painter->drawPixmap(658,45,36,60,qpixmap6);
        }
        else {
            painter->drawPixmap(595,45,30,50,qpixmap4);
            painter->drawPixmap(625,45,30,50,qpixmap5);
            painter->drawPixmap(655,45,30,50,qpixmap6);
        }
    }
    if (1000<=num&&num<10000){
        int COMBONUM[4];
        int t=num;
        QPixmap qpixcom[4];
        for (int i=3;i>=0;i--){
            COMBONUM[i]=t-t/10*10;
            t=t/10;
            qpixcom[i].load(YOUKY::FCombo[COMBONUM[i]]);
        }
        if (isBig){
            for (int i=0;i<4;i++){
                painter->drawPixmap(568+36*i,45,36,60,qpixcom[i]);
            }
        }
        else {
            for (int i=0;i<4;i++){
                painter->drawPixmap(580+30*i,45,30,50,qpixcom[i]);
            }
        }
    }
    painter->restore();
}
