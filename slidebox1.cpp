#include "slidebox1.h"
#include "ui_slidebox1.h"
#include "QGraphicsEffect"
#include "QMessageBox"
#include"QPropertyAnimation"

SlideBox1::SlideBox1(int NOS , QString *NL ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SlideBox1)
{
    ui->setupUi(this);

    for(int i=0;i<7;i++){
        heightOfFakeButton[i]=50;
        widthOfFakeButton[i]=300;
        xOfFakeButton[i]=50;
    }
    xOfFakeButton[3]=0;
    yOfFakeButton[3]=240;
    heightOfFakeButton[3]=80;
    widthOfFakeButton[3]=350;

    yOfFakeButton[0]=20;
    yOfFakeButton[1]=90;
    yOfFakeButton[2]=160;
    yOfFakeButton[3]=240;
    yOfFakeButton[4]=350;
    yOfFakeButton[5]=420;
    yOfFakeButton[6]=490;

    ui->upPage->raise();
    ui->downPage->raise();
    ui->chooseButton->raise();

    cT=0;
    numberOfSongs = NOS ;
    songName = NL;

    upPageE = new QGraphicsOpacityEffect(ui->upPage);
    upPageE->setOpacity(0);
    ui->upPage->setGraphicsEffect(upPageE);
    downPageE = new QGraphicsOpacityEffect(ui->downPage);
    downPageE->setOpacity(0);
    ui->downPage->setGraphicsEffect(downPageE);

    sb = new QGraphicsOpacityEffect(ui->chooseButton);
    sb->setOpacity(0);
    ui->chooseButton->setGraphicsEffect(sb);

    ptf[0] = ui->fakeButton1;
    ptf[1] = ui->fakeButton2;
    ptf[2] = ui->fakeButton3;
    ptf[3] = ui->fakeButton4;
    ptf[4] = ui->fakeButton5;
    ptf[5] = ui->fakeButton6;
    ptf[6] = ui->fakeButton7;
    for(int i = 0; i < 7 ; i++)
    ptf[i]->setText(songName[i%numberOfSongs]);

  //  ptf[0]->setGeometry(100,0,100,400);

//    connect(ui->upPage,SIGNAL(clicked()),this,SLOT(close()));

}




SlideBox1::~SlideBox1()
{
    delete ui;
}


void SlideBox1::on_downPage_clicked()
{

    emit downPagePressed();


 //   QString a;
  //  a =QString::number(this->width());
  //  QMessageBox::about(this,"ds",a );
  /*  slide1 = new QPropertyAnimation(ptf[(cT)%7],"geometry");
    slide1->setDuration(400);
    slide1->setStartValue(QRect(xOfFakeButton[0],yOfFakeButton[0],widthOfFakeButton[0],heightOfFakeButton[0]));
    slide1->setEndValue(QRect(xOfFakeButton[1], yOfFakeButton[1], widthOfFakeButton[1], heightOfFakeButton[1]));
    slide1->setEasingCurve(QEasingCurve::InOutBack);

    slide2 = new QPropertyAnimation(ptf[(cT+1)%7],"geometry");
    slide2->setDuration(400);
    slide2->setStartValue(QRect(xOfFakeButton[1],yOfFakeButton[1],widthOfFakeButton[1],heightOfFakeButton[1]));
    slide2->setEndValue(QRect(xOfFakeButton[2], yOfFakeButton[2], widthOfFakeButton[2], heightOfFakeButton[2]));
    slide2->setEasingCurve(QEasingCurve::InOutBack);

    slide3 = new QPropertyAnimation(ptf[(cT+2)%7],"geometry");
    slide3->setDuration(400);
    slide3->setStartValue(QRect(xOfFakeButton[2],yOfFakeButton[2],widthOfFakeButton[2],heightOfFakeButton[2]));
    slide3->setEndValue(QRect(xOfFakeButton[3], yOfFakeButton[3], widthOfFakeButton[3], heightOfFakeButton[3]));
    slide3->setEasingCurve(QEasingCurve::InOutBack);

    slide4 = new QPropertyAnimation(ptf[(cT+3)%7],"geometry");
    slide4->setDuration(400);
    slide4->setStartValue(QRect(xOfFakeButton[3],yOfFakeButton[3],widthOfFakeButton[3],heightOfFakeButton[3]));
    slide4->setEndValue(QRect(xOfFakeButton[4], yOfFakeButton[4], widthOfFakeButton[4], heightOfFakeButton[4]));
    slide4->setEasingCurve(QEasingCurve::InOutBack);

    slide5 = new QPropertyAnimation(ptf[(cT+4)%7],"geometry");
    slide5->setDuration(400);
    slide5->setStartValue(QRect(xOfFakeButton[4],yOfFakeButton[4],widthOfFakeButton[4],heightOfFakeButton[4]));
    slide5->setEndValue(QRect(xOfFakeButton[5], yOfFakeButton[5], widthOfFakeButton[5], heightOfFakeButton[5]));
    slide5->setEasingCurve(QEasingCurve::InOutBack);

    slide6 = new QPropertyAnimation(ptf[(cT+5)%7],"geometry");
    slide6->setDuration(400);
    slide6->setStartValue(QRect(xOfFakeButton[5],yOfFakeButton[5],widthOfFakeButton[5],heightOfFakeButton[5]));
    slide6->setEndValue(QRect(xOfFakeButton[6], yOfFakeButton[6], widthOfFakeButton[6], heightOfFakeButton[6]));
    slide6->setEasingCurve(QEasingCurve::InOutBack);

    slide7 = new QPropertyAnimation(ptf[(cT+6)%7],"geometry");
    slide7->setDuration(400);
    slide7->setStartValue(QRect(xOfFakeButton[6],yOfFakeButton[6],widthOfFakeButton[6],heightOfFakeButton[6]));
    slide7->setEndValue(QRect(xOfFakeButton[0], yOfFakeButton[0], widthOfFakeButton[0], heightOfFakeButton[0]));
    slide7->setEasingCurve(QEasingCurve::InOutBack);

    slide1->start(QAbstractAnimation::DeleteWhenStopped);
    slide2->start(QAbstractAnimation::DeleteWhenStopped);
    slide3->start(QAbstractAnimation::DeleteWhenStopped);
    slide4->start(QAbstractAnimation::DeleteWhenStopped);
    slide5->start(QAbstractAnimation::DeleteWhenStopped);
    slide6->start(QAbstractAnimation::DeleteWhenStopped);
    slide7->start(QAbstractAnimation::DeleteWhenStopped);*/

    SlideAnimDown *dons;
    dons = new SlideAnimDown(xOfFakeButton,yOfFakeButton, widthOfFakeButton, heightOfFakeButton,this,cT,ptf);
    dons->start(QAbstractAnimation::DeleteWhenStopped);

    cT = cT - 1;
    if (cT<0)cT=6;
    if (cT>7)cT=0;

    id--;
    if (id>=numberOfSongs)id=0;
    if (id<0)id=numberOfSongs-1;

    ptf[(cT+7)%7]->setText(songName[(id+6)%numberOfSongs]);
}



void SlideBox1::upDateSizes(){

    int w,h;
    w = this->width();
    h = this->height();

    for ( int i = 0 ; i < 7 ; i++ ){

        heightOfFakeButton[i]=h*50/600;
        widthOfFakeButton[i]=w*300/350;
        xOfFakeButton[i]=w*50/300;
    }
    xOfFakeButton[(cT+3)%7]=0;
    yOfFakeButton[(cT+3)%7]=h*240/300;
    heightOfFakeButton[(cT+3)%7]=h*80/600;
    widthOfFakeButton[(cT+3)%7]=w;

    yOfFakeButton[(cT+0)%7]=h*20/600;
    yOfFakeButton[(cT+1)%7]=h*90/600;
    yOfFakeButton[(cT+2)%7]=h*160/600;
    yOfFakeButton[(cT+3)%7]=h*240/600;
    yOfFakeButton[(cT+4)%7]=h*350/600;
    yOfFakeButton[(cT+5)%7]=h*420/600;
    yOfFakeButton[(cT+6)%7]=h*490/600;

    for ( int i = 0 ; i < 7 ; i++ ){
        ptf[i]->setGeometry(xOfFakeButton[i],yOfFakeButton[i],widthOfFakeButton[i],heightOfFakeButton[i]);
    }

    ui->upPage->setGeometry(w*30/350,h*5/600,w*320/350,h*220/600);
    ui->downPage->setGeometry(w*30/350,h*335/600,w*320/350,h*220/600);
    ui->chooseButton->setGeometry(0,h*240/600,w,h*80/600);

}

void SlideBox1::on_upPage_clicked()
{
    emit upPagePressed();
    /*slide1 = new QPropertyAnimation(ptf[(cT+6)%7],"geometry");
    slide1->setDuration(400);
    slide1->setStartValue(QRect(xOfFakeButton[6],yOfFakeButton[6],widthOfFakeButton[6],heightOfFakeButton[6]));
    slide1->setEndValue(QRect(xOfFakeButton[5], yOfFakeButton[5], widthOfFakeButton[5], heightOfFakeButton[5]));
    slide1->setEasingCurve(QEasingCurve::InOutBack);

 //   this->close();

    slide2 = new QPropertyAnimation(ptf[(cT+5)%7],"geometry");
    slide2->setDuration(400);
    slide2->setStartValue(QRect(xOfFakeButton[5],yOfFakeButton[5],widthOfFakeButton[5],heightOfFakeButton[5]));
    slide2->setEndValue(QRect(xOfFakeButton[4], yOfFakeButton[4], widthOfFakeButton[4], heightOfFakeButton[4]));
    slide2->setEasingCurve(QEasingCurve::InOutBack);

    slide3 = new QPropertyAnimation(ptf[(cT+4)%7],"geometry");
    slide3->setDuration(400);
    slide3->setStartValue(QRect(xOfFakeButton[4],yOfFakeButton[4],widthOfFakeButton[4],heightOfFakeButton[4]));
    slide3->setEndValue(QRect(xOfFakeButton[3], yOfFakeButton[3], widthOfFakeButton[3], heightOfFakeButton[3]));
    slide3->setEasingCurve(QEasingCurve::InOutBack);

    slide4 = new QPropertyAnimation(ptf[(cT+3)%7],"geometry");
    slide4->setDuration(400);
    slide4->setStartValue(QRect(xOfFakeButton[3],yOfFakeButton[3],widthOfFakeButton[3],heightOfFakeButton[3]));
    slide4->setEndValue(QRect(xOfFakeButton[2], yOfFakeButton[2], widthOfFakeButton[2], heightOfFakeButton[2]));
    slide4->setEasingCurve(QEasingCurve::InOutBack);
//this->close();
 //   QString a;
 //   a =QString::number(this->height());
  //  QMessageBox::about(this,"ds",a );
    slide5 = new QPropertyAnimation(ptf[(cT+2)%7],"geometry");
    slide5->setDuration(400);
    slide5->setStartValue(QRect(xOfFakeButton[2],yOfFakeButton[2],widthOfFakeButton[2],heightOfFakeButton[2]));
    slide5->setEndValue(QRect(xOfFakeButton[1], yOfFakeButton[1], widthOfFakeButton[1], heightOfFakeButton[1]));
    slide5->setEasingCurve(QEasingCurve::InOutBack);

    slide6 = new QPropertyAnimation(ptf[(cT+1)%7],"geometry");
    slide6->setDuration(400);
    slide6->setStartValue(QRect(xOfFakeButton[1],yOfFakeButton[1],widthOfFakeButton[1],heightOfFakeButton[1]));
    slide6->setEndValue(QRect(xOfFakeButton[0], yOfFakeButton[0], widthOfFakeButton[0], heightOfFakeButton[0]));
    slide6->setEasingCurve(QEasingCurve::InOutBack);

    slide7 = new QPropertyAnimation(ptf[(cT)%7],"geometry");
    slide7->setDuration(400);
    slide7->setStartValue(QRect(xOfFakeButton[0],yOfFakeButton[0],widthOfFakeButton[0],heightOfFakeButton[0]));
    slide7->setEndValue(QRect(xOfFakeButton[6], yOfFakeButton[6], widthOfFakeButton[6], heightOfFakeButton[6]));
    slide7->setEasingCurve(QEasingCurve::InOutBack);

    slide1->start(QAbstractAnimation::DeleteWhenStopped);
    slide2->start(QAbstractAnimation::DeleteWhenStopped);
    slide3->start(QAbstractAnimation::DeleteWhenStopped);
    slide4->start(QAbstractAnimation::DeleteWhenStopped);
    slide5->start(QAbstractAnimation::DeleteWhenStopped);
    slide6->start(QAbstractAnimation::DeleteWhenStopped);
    slide7->start(QAbstractAnimation::DeleteWhenStopped);

 //   QString a;
 //   a =QString::number((9)%7);
 //   QMessageBox::about(this,"ds",a );
 //   slide01->start();
   */
    SlideAnimUp * upps;

    upps = new SlideAnimUp(xOfFakeButton,yOfFakeButton, widthOfFakeButton, heightOfFakeButton,this,cT,ptf);

    upps->start(QAbstractAnimation::DeleteWhenStopped);

    cT = cT + 1;
    if (cT>=7)cT=0;
    if(cT<0)cT=6;

    id++;
    if (id>=numberOfSongs)id=0;
    if (id<0)id=numberOfSongs-1;

    ptf[(cT+6)%7]->setText(songName[(id+6)%numberOfSongs]);

}

void SlideBox1::resizeEvent(QResizeEvent *){
    upDateSizes();
}
