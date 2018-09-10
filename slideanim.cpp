#include "slideanim.h"
#include "slidebox1.h"
#include <algorithm>
#include <QMessageBox>
#include <QString>

SlideAnimUp::SlideAnimUp(int x[], int y[],int w[],int h[] ,QObject *parent1=NULL , int Clock=0 ,QPushButton* ptf[]=NULL):QParallelAnimationGroup ( parent1 ), cT(Clock)
{
    int xOfFakeButton[7],yOfFakeButton[7],widthOfFakeButton[7],heightOfFakeButton[7];

 /*      QString a;
       a =QString::number((9)%7);
       QMessageBox::about(NULL,"ds",a );*/

    for ( int i = 0 ; i<7; i++ ){
        widthOfFakeButton[i]=w[(i)%7];
        heightOfFakeButton[i]=h[(i)%7];
        xOfFakeButton[i]=x[(i)%7];
        yOfFakeButton[i]=y[(i)%7];
    }


    Sslide1 = new QPropertyAnimation(ptf[(cT+6)%7],"geometry");
    Sslide1->setDuration(400);
    Sslide1->setStartValue(QRect(xOfFakeButton[6],yOfFakeButton[6],widthOfFakeButton[6],heightOfFakeButton[6]));
    Sslide1->setEndValue(QRect(xOfFakeButton[5], yOfFakeButton[5], widthOfFakeButton[5], heightOfFakeButton[5]));
    Sslide1->setEasingCurve(QEasingCurve::InOutBack);

 //   this->close();

    Sslide2 = new QPropertyAnimation(ptf[(cT+5)%7],"geometry");
    Sslide2->setDuration(400);
    Sslide2->setStartValue(QRect(xOfFakeButton[5],yOfFakeButton[5],widthOfFakeButton[5],heightOfFakeButton[5]));
    Sslide2->setEndValue(QRect(xOfFakeButton[4], yOfFakeButton[4], widthOfFakeButton[4], heightOfFakeButton[4]));
    Sslide2->setEasingCurve(QEasingCurve::InOutBack);

    Sslide3 = new QPropertyAnimation(ptf[(cT+4)%7],"geometry");
    Sslide3->setDuration(400);
    Sslide3->setStartValue(QRect(xOfFakeButton[4],yOfFakeButton[4],widthOfFakeButton[4],heightOfFakeButton[4]));
    Sslide3->setEndValue(QRect(xOfFakeButton[3], yOfFakeButton[3], widthOfFakeButton[3], heightOfFakeButton[3]));
    Sslide3->setEasingCurve(QEasingCurve::InOutBack);

    Sslide4 = new QPropertyAnimation(ptf[(cT+3)%7],"geometry");
    Sslide4->setDuration(400);
    Sslide4->setStartValue(QRect(xOfFakeButton[3],yOfFakeButton[3],widthOfFakeButton[3],heightOfFakeButton[3]));
    Sslide4->setEndValue(QRect(xOfFakeButton[2], yOfFakeButton[2], widthOfFakeButton[2], heightOfFakeButton[2]));
    Sslide4->setEasingCurve(QEasingCurve::InOutBack);
//this->close();
 //   QString a;
 //   a =QString::number(this->height());
  //  QMessageBox::about(this,"ds",a );
    Sslide5 = new QPropertyAnimation(ptf[(cT+2)%7],"geometry");
    Sslide5->setDuration(400);
    Sslide5->setStartValue(QRect(xOfFakeButton[2],yOfFakeButton[2],widthOfFakeButton[2],heightOfFakeButton[2]));
    Sslide5->setEndValue(QRect(xOfFakeButton[1], yOfFakeButton[1], widthOfFakeButton[1], heightOfFakeButton[1]));
    Sslide5->setEasingCurve(QEasingCurve::InOutBack);

    Sslide6 = new QPropertyAnimation(ptf[(cT+1)%7],"geometry");
    Sslide6->setDuration(400);
    Sslide6->setStartValue(QRect(xOfFakeButton[1],yOfFakeButton[1],widthOfFakeButton[1],heightOfFakeButton[1]));
    Sslide6->setEndValue(QRect(xOfFakeButton[0], yOfFakeButton[0], widthOfFakeButton[0], heightOfFakeButton[0]));
    Sslide6->setEasingCurve(QEasingCurve::InOutBack);

    Sslide7 = new QPropertyAnimation(ptf[(cT)%7],"geometry");
    Sslide7->setDuration(400);
    Sslide7->setStartValue(QRect(xOfFakeButton[0],yOfFakeButton[0],widthOfFakeButton[0],heightOfFakeButton[0]));
    Sslide7->setEndValue(QRect(xOfFakeButton[6], yOfFakeButton[6], widthOfFakeButton[6], heightOfFakeButton[6]));
    Sslide7->setEasingCurve(QEasingCurve::InOutBack);

    this->addAnimation(Sslide1);
    this->addAnimation(Sslide2);
    this->addAnimation(Sslide3);
    this->addAnimation(Sslide4);
    this->addAnimation(Sslide5);
    this->addAnimation(Sslide6);
    this->addAnimation(Sslide7);
}


SlideAnimDown::SlideAnimDown(int x[], int y[],int w[],int h[],QObject *parent1=NULL , int Clock=0 ,QPushButton* ptf[]=NULL):QParallelAnimationGroup ( parent1 ), cT(Clock)
{
    int xOfFakeButton[7],yOfFakeButton[7],widthOfFakeButton[7],heightOfFakeButton[7];

 /*      QString a;
       a =QString::number((9)%7);
       QMessageBox::about(NULL,"ds",a );*/

    for ( int i = 0 ; i<7; i++ ){
        widthOfFakeButton[i]=w[(i)%7];
        heightOfFakeButton[i]=h[(i)%7];
        xOfFakeButton[i]=x[(i)%7];
        yOfFakeButton[i]=y[(i)%7];
    }


    Sslide1 = new QPropertyAnimation(ptf[(cT)%7],"geometry");
    Sslide1->setDuration(400);
    Sslide1->setStartValue(QRect(xOfFakeButton[0],yOfFakeButton[0],widthOfFakeButton[0],heightOfFakeButton[0]));
    Sslide1->setEndValue(QRect(xOfFakeButton[1], yOfFakeButton[1], widthOfFakeButton[1], heightOfFakeButton[1]));
    Sslide1->setEasingCurve(QEasingCurve::InOutBack);

    Sslide2 = new QPropertyAnimation(ptf[(cT+1)%7],"geometry");
    Sslide2->setDuration(400);
    Sslide2->setStartValue(QRect(xOfFakeButton[1],yOfFakeButton[1],widthOfFakeButton[1],heightOfFakeButton[1]));
    Sslide2->setEndValue(QRect(xOfFakeButton[2], yOfFakeButton[2], widthOfFakeButton[2], heightOfFakeButton[2]));
    Sslide2->setEasingCurve(QEasingCurve::InOutBack);

    Sslide3 = new QPropertyAnimation(ptf[(cT+2)%7],"geometry");
    Sslide3->setDuration(400);
    Sslide3->setStartValue(QRect(xOfFakeButton[2],yOfFakeButton[2],widthOfFakeButton[2],heightOfFakeButton[2]));
    Sslide3->setEndValue(QRect(xOfFakeButton[3], yOfFakeButton[3], widthOfFakeButton[3], heightOfFakeButton[3]));
    Sslide3->setEasingCurve(QEasingCurve::InOutBack);

    Sslide4 = new QPropertyAnimation(ptf[(cT+3)%7],"geometry");
    Sslide4->setDuration(400);
    Sslide4->setStartValue(QRect(xOfFakeButton[3],yOfFakeButton[3],widthOfFakeButton[3],heightOfFakeButton[3]));
    Sslide4->setEndValue(QRect(xOfFakeButton[4], yOfFakeButton[4], widthOfFakeButton[4], heightOfFakeButton[4]));
    Sslide4->setEasingCurve(QEasingCurve::InOutBack);

    Sslide5 = new QPropertyAnimation(ptf[(cT+4)%7],"geometry");
    Sslide5->setDuration(400);
    Sslide5->setStartValue(QRect(xOfFakeButton[4],yOfFakeButton[4],widthOfFakeButton[4],heightOfFakeButton[4]));
    Sslide5->setEndValue(QRect(xOfFakeButton[5], yOfFakeButton[5], widthOfFakeButton[5], heightOfFakeButton[5]));
    Sslide5->setEasingCurve(QEasingCurve::InOutBack);

    Sslide6 = new QPropertyAnimation(ptf[(cT+5)%7],"geometry");
    Sslide6->setDuration(400);
    Sslide6->setStartValue(QRect(xOfFakeButton[5],yOfFakeButton[5],widthOfFakeButton[5],heightOfFakeButton[5]));
    Sslide6->setEndValue(QRect(xOfFakeButton[6], yOfFakeButton[6], widthOfFakeButton[6], heightOfFakeButton[6]));
    Sslide6->setEasingCurve(QEasingCurve::InOutBack);

    Sslide7 = new QPropertyAnimation(ptf[(cT+6)%7],"geometry");
    Sslide7->setDuration(400);
    Sslide7->setStartValue(QRect(xOfFakeButton[6],yOfFakeButton[6],widthOfFakeButton[6],heightOfFakeButton[6]));
    Sslide7->setEndValue(QRect(xOfFakeButton[0], yOfFakeButton[0], widthOfFakeButton[0], heightOfFakeButton[0]));
    Sslide7->setEasingCurve(QEasingCurve::InOutBack);

    this->addAnimation(Sslide1);
    this->addAnimation(Sslide2);
    this->addAnimation(Sslide3);
    this->addAnimation(Sslide4);
    this->addAnimation(Sslide5);
    this->addAnimation(Sslide6);
    this->addAnimation(Sslide7);
}
