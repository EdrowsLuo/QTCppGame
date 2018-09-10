#ifndef SLIDEANIM_H
#define SLIDEANIM_H

#include <QAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QPushButton>

class SlideAnimUp : public QParallelAnimationGroup
{
public:
    SlideAnimUp(int x[], int y[],int w[],int h[],QObject *parent1 , int Clock ,QPushButton* ptf[]);

    QPropertyAnimation *Sslide1,*Sslide2,*Sslide3,*Sslide4,*Sslide5,*Sslide6,*Sslide7;
    int cT;

};

class SlideAnimDown : public QParallelAnimationGroup
{
public:
    SlideAnimDown(int x[], int y[],int w[],int h[],QObject *parent1 , int Clock ,QPushButton* ptf[]);

    QPropertyAnimation *Sslide1,*Sslide2,*Sslide3,*Sslide4,*Sslide5,*Sslide6,*Sslide7;
    int cT;

};

#endif // SLIDEANIM_H
