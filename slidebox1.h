#ifndef SLIDEBOX1_H
#define SLIDEBOX1_H

#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QPushButton>
#include <QPropertyAnimation>
#include "slideanim.h"
#include "cJSON.h"

namespace Ui {
    class SlideBox1;
}

class SlideBox1 : public QWidget
{
    Q_OBJECT


public:

    QGraphicsOpacityEffect *upPageE,*downPageE,*sb;

    explicit SlideBox1( int  , QString * ,QWidget *parent = 0);
    ~SlideBox1();

    QPushButton *ptf[7];
    QPropertyAnimation *slide1,*slide2,*slide3,*slide4,*slide5,*slide6,*slide7;

    int cT;
    int id;
    int numberOfSongs;

    int heightOfFakeButton[7] , HOUB,HODB,HOCB;
    int widthOfFakeButton[7], WOUB,WODB,WOCB;
    int xOfFakeButton[7],XOUB,XODB,XOCB;
    int yOfFakeButton[7],YOUB,YODB,YOCB;

    QString *songName;


public slots:
//  void on_upPage_clicked();
//   void odp();

signals:

    void upPagePressed();
    void downPagePressed();

private slots:
   void on_downPage_clicked();

   void on_upPage_clicked();

private:
    Ui::SlideBox1 *ui;
    void upDateSizes();

protected:
    void resizeEvent(QResizeEvent *);


};

#endif // SLIDEBOX1_H
