#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "slidebox1.h"
#include "difficultyscrollarea.h"
#include "QHBoxLayout"
#include <QAction>
#include "ui_slidebox1.h"
#include "defext.h"
#include "CJsonObject.hpp"
#include "songgroup.h"
#include "settings.h"

using namespace nso;
using namespace neb;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{

    //  testwidget = new Widgettest(this);
    //   testwidget->show();
    ui->setupUi(this);

    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(40,44,53)));

    s = SongGroup();
    /* EdpFile out(*Project::ProjectRoot,"assets\\songs\\songs.json");
     string str;
     IOUtil::readFull(out,str);
     CJsonObject object(str);
     CJsonObject *basicData;
*/
    ss = new QString[s.Number];
    for ( int i = 0 ; i<s.Number ; i++ ){
        ss[i] = s.songlist[i].songsName.c_str();
    }

    SN = 0;
    ST = 0;
    al=1;
    modeNumber=0;

    ui->StartButton->raise();
    ui->SetButton->raise();
    ui->label->raise();
    ui->ExitButton->raise();

    gameview = new Widget(this);
    //connect(gameview, SIGNAL(omGameStart()), this, SLOT(onGameStart()));
    connect(gameview, SIGNAL(GameEnd()), this, SLOT(GAMEEND()));
    gameview->close();


    RightBox = new SlideBox1(s.Number,ss,this);
    RightBox->setObjectName("sid");
    RightBox->setStyleSheet("QWidget#RightBox{background-color:transparent}");

    connect(RightBox,SIGNAL(downPagePressed()),this,SLOT(SN_ADD()));
    connect(RightBox,SIGNAL(upPagePressed()),this,SLOT(SN_SUB()));

    LeftBox[(SN+100)%2]=new DifficultyScrollArea( s.songlist[3] ,this);
    LeftBox[(SN+100)%2]->setObjectName("dou");
    connect(LeftBox[((SN+100))%2]->my_splitter,SIGNAL(StartGame()),this,SLOT(InitialGame()));
    leftBoxDisappear=new QPropertyAnimation( this );
    leftBoxDisappear->setPropertyName("geometry");
    leftBoxAppear = new QPropertyAnimation (this);
    leftBoxAppear->setPropertyName("geometry");
    connect(leftBoxDisappear,SIGNAL(finished()),this,SLOT(SN_SUB_ANIM1()));


    startButtonDisappear=new QPropertyAnimation(ui->StartButton,"geometry",this);
    setButtonDisappear=new QPropertyAnimation(ui->SetButton,"geometry",this);
    exitButtonDisappear=new QPropertyAnimation(ui->ExitButton,"geometry",this);
    titleDisappear=new QPropertyAnimation(ui->label,"geometry",this);
    connect(startButtonDisappear,SIGNAL(finished()),this,SLOT(onChooseSurfaceAppear()));

    startButtonAppear=new QPropertyAnimation(ui->StartButton,"geometry",this);
    setButtonAppear=new QPropertyAnimation(ui->SetButton,"geometry",this);
    exitButtonAppear=new QPropertyAnimation(ui->ExitButton,"geometry",this);
    titleAppear=new QPropertyAnimation(ui->label,"geometry",this);

    leftBoxAppear0=new QPropertyAnimation(this);
    leftBoxDisappear0=new QPropertyAnimation(this);
    LeftBox[(SN+100)%2]->close();



    rightBoxAppear0 =new QPropertyAnimation(RightBox,"geometry",this);
    rightBoxDisappear0 =new QPropertyAnimation(RightBox,"geometry",this);
    RightBox->close();

    upButtonAppear=new QPropertyAnimation(ui->upButton,"geometry",this);
    upButtonDisappear=new QPropertyAnimation(ui->upButton,"geometry",this);
    ui->upButton->close();

    connect(upButtonDisappear,SIGNAL(finished()),this,SLOT(onStartSurfaceAppear()));

    ui->ModeButton1->close();
    modeButtonAppear=new QPropertyAnimation(ui->ModeButton1,"geometry",this);
    modeButtonDisappear=new QPropertyAnimation(ui->ModeButton1,"geometry",this);

    leftBoxDisappear01 = new QPropertyAnimation(this);
    leftBoxDisappear01->setPropertyName("geometry");
    modeButtonDisappear01=new QPropertyAnimation(ui->ModeButton1,"geometry",this);
    upButtonDisappear01=new QPropertyAnimation(ui->upButton,"geometry",this);
    rightBoxDisappear01 =new QPropertyAnimation(RightBox,"geometry",this);
    connect(modeButtonDisappear01,SIGNAL(finished()),this,SLOT(GAMESTART()));

    leftBoxAppear01 = new QPropertyAnimation(this);
    leftBoxAppear01->setPropertyName("geometry");
    modeButtonAppear01 = new QPropertyAnimation(ui->ModeButton1,"geometry",this);
    upButtonAppear01 = new QPropertyAnimation(ui->upButton,"geometry",this);
    rightBoxAppear01 = new QPropertyAnimation(RightBox,"geometry",this);

    Settings *SetSurface = new Settings;

}

void MainWindow::SongACopyB( Songs * a , Songs * b ){
    a->songNumber = b->songNumber;
}



void MainWindow::UpDateSize(){
    int w,h;
    w = this->width();
    h = this->height();
    this->RightBox->setGeometry(QRect(490*w/800,11*h/600,310*w/800,h));
    this->LeftBox[(SN+100)%2]->setGeometry(QRect(11*w/800,40*h/600,422*w/800,510*h/600));
    lx = 11*w/800;
    ly = 40*h/600;
    lw = 422*w/800;
    lh = 510*h/600;
    rx = 490*w/800;
    ry = 11*h/600;
    rw = 310*w/800;
    rh = h;
    ux = 370*w/800; mx = 370*w/800;
    uy = -30; my = 550*h/600;
    uw = 60*w/800; mw = 60*w/800;
    uh = 60*h/600; mh = 60*h/600;
    ui->upButton->setGeometry(QRect(ux,uy,uw,uh));
    ui->ModeButton1->setGeometry(QRect(mx,my,mw,mh));
    sx = 300*w/800;
    sy = 200*h/600;
    sw = 200*w/800;
    sh = 90*h/600;
    sd = 100*h/600;
    ui->StartButton->setGeometry(QRect(sx,sy,sw,sh));
    ui->SetButton->setGeometry(QRect(sx,sy+sd,sw,sh));
    ui->ExitButton->setGeometry(QRect(sx,sy+sd+sd,sw,sh));
    lbx = 300*w/800;
    lby = 50*h/600;
    lbw = 200*w/800;
    lbh = 70*h/600;
    ui->label->setGeometry(QRect(lbx,lby,lbw,lbh));
    gw=this->width();
    gh=this->height();
    gameview->setGeometry(QRect(0,0,gw,gh));

}
void MainWindow::resizeEvent(QResizeEvent *){
    UpDateSize();
    //   if(this->height()!=this->width()*6/8)
    //   this->setGeometry(QRect(this->x(),this->y(),this->width(),this->width()*6/8));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartButton_clicked()
{
    leftBoxAppear0->setTargetObject(LeftBox[(SN+100)%2]);
    leftBoxAppear0->setPropertyName("geometry");

    startButtonDisappear->setStartValue(QRect(ui->StartButton->geometry()));
    startButtonDisappear->setEndValue(QRect(ui->StartButton->x(),0-ui->StartButton->height(),ui->StartButton->width(),ui->StartButton->height()));
    startButtonDisappear->setDuration(400);
    startButtonDisappear->setEasingCurve(QEasingCurve::InBack);
    startButtonDisappear->start();

    setButtonDisappear->setStartValue(QRect(ui->SetButton->geometry()));
    setButtonDisappear->setEndValue(QRect(ui->SetButton->x(),0-ui->SetButton->height(),ui->SetButton->width(),ui->SetButton->height()));
    setButtonDisappear->setDuration(400);
    setButtonDisappear->setEasingCurve(QEasingCurve::InBack);
    setButtonDisappear->start();

    exitButtonDisappear->setStartValue(QRect(ui->ExitButton->geometry()));
    exitButtonDisappear->setEndValue(QRect(ui->ExitButton->x(),0-ui->ExitButton->height(),ui->ExitButton->width(),ui->ExitButton->height()));
    exitButtonDisappear->setDuration(400);
    exitButtonDisappear->setEasingCurve(QEasingCurve::InBack);
    exitButtonDisappear->start();

    titleDisappear->setStartValue(QRect(ui->label->geometry()));
    titleDisappear->setEndValue(QRect(ui->label->x(),0-ui->label->height(),ui->label->width(),ui->label->height()));
    titleDisappear->setDuration(400);
    titleDisappear->setEasingCurve(QEasingCurve::InBack);
    titleDisappear->start();

    string place = "assets\\songs\\" + s.songlist[(ST+s.Number+3)%s.Number].fileName;
    place = place + "\\";
    place = place + s.songlist[(ST+s.Number+3)%s.Number].difficultylist[0].audiofilename;
    EdpFile f(*Project::ProjectRoot,place);
    string fullpath = f.getFullPath();
    Project::ProjectGame->loadMusic(fullpath,s.songlist[(ST+s.Number+3)%s.Number].difficultylist[0].previewtime);

}


void MainWindow::onChooseSurfaceAppear(){
    ui->StartButton->close();
    ui->SetButton->close();
    ui->ExitButton->close();
    ui->label->close();
    ui->upButton->setGeometry(QRect(ux,-30-uh,uw,uh));
    ui->upButton->show();
    ui->ModeButton1->show();

    LeftBox[(SN+100)%2]->show();
    RightBox->show();



    upButtonAppear->setStartValue(QRect(ux,uy-uh,uw,uh));
    upButtonAppear->setEndValue(QRect(ux,uy,uw,uh));
    upButtonAppear->setDuration(1000);
    upButtonAppear->setEasingCurve(QEasingCurve::OutCirc);
    upButtonAppear->start();

    modeButtonAppear->setStartValue(QRect(mx,this->height()+mh,mw,mh));
    modeButtonAppear->setEndValue(QRect(mx,my,mw,mh));
    modeButtonAppear->setDuration(800);
    modeButtonAppear->setEasingCurve(QEasingCurve::OutBack);
    modeButtonAppear->start();

    LeftBox[(SN+100)%2]->show();
    //  LeftBox[SN%2]->setGeometry(QRect(lx,ly,lw,lh));
    leftBoxAppear0->setStartValue(QRect(0-lw,ly,lw,lh));
    leftBoxAppear0->setEndValue(QRect(lx,ly,lw,lh));
    leftBoxAppear0->setDuration(800);
 //   leftBoxAppear0->setEasingCurve();
    leftBoxAppear0->start();

    RightBox->show();
    //  LeftBox[SN%2]->setGeometry(QRect(rx,ry,rw,rh));
    rightBoxAppear0->setStartValue(QRect(this->width()+rw,ry,rw,rh));
    rightBoxAppear0->setEndValue(QRect(rx,ry,rw,rh));
    rightBoxAppear0->setDuration(800);
    rightBoxAppear0->setEasingCurve(QEasingCurve::OutBack);
    rightBoxAppear0->start();
}

void MainWindow::on_upButton_clicked()
{
    leftBoxDisappear0->setTargetObject(LeftBox[(SN+100)%2]);
    leftBoxDisappear0->setPropertyName("geometry");

    upButtonDisappear->setStartValue(QRect(ux,uy,uw,uh));
    upButtonDisappear->setEndValue(QRect(ux,uy-uh,uw,uh));
    upButtonDisappear->setDuration(800);
    upButtonDisappear->setEasingCurve(QEasingCurve::InBack);
    upButtonDisappear->start();

    modeButtonDisappear->setStartValue(QRect(mx,my,mw,mh));
    modeButtonDisappear->setEndValue(QRect(mx,this->height()+mh,mw,mh));
    modeButtonDisappear->setDuration(800);
    modeButtonDisappear->setEasingCurve(QEasingCurve::InBack);
    modeButtonDisappear->start();

    leftBoxDisappear0->setStartValue(QRect(lx,ly,lw,lh));
    leftBoxDisappear0->setEndValue(QRect(0-lw,ly,lw,lh));
    leftBoxDisappear0->setDuration(800);
    //leftBoxDisappear0->setEasingCurve();
    leftBoxDisappear0->start();

    rightBoxDisappear0->setStartValue(QRect(rx,ry,rw,rh));
    rightBoxDisappear0->setEndValue(QRect(this->width()+rw,ry,rw,rh));
    rightBoxDisappear0->setDuration(800);
    rightBoxDisappear0->setEasingCurve(QEasingCurve::InBack);
    rightBoxDisappear0->start();
}

void MainWindow::onStartSurfaceAppear(){
    ui->upButton->close();
    RightBox->close();
    LeftBox[(SN+100)%2]->close();
    ui->StartButton->show();
    ui->SetButton->show();
    ui->ExitButton->show();
    ui->label->show();

    startButtonAppear->setStartValue(QRect(sx,0-sh,sw,sh));
    startButtonAppear->setEndValue(QRect(sx,sy,sw,sh));
    startButtonAppear->setDuration(400);
    startButtonAppear->setEasingCurve(QEasingCurve::OutBack);
    startButtonAppear->start();

    setButtonAppear->setStartValue(QRect(sx,0-sh,sw,sh));
    setButtonAppear->setEndValue(QRect(sx,sy+sd,sw,sh));
    setButtonAppear->setDuration(400);
    setButtonAppear->setEasingCurve(QEasingCurve::OutBack);
    setButtonAppear->start();

    exitButtonAppear->setStartValue(QRect(sx,0-sh,sw,sh));
    exitButtonAppear->setEndValue(QRect(sx,sy+sd+sd,sw,sh));
    exitButtonAppear->setDuration(400);
    exitButtonAppear->setEasingCurve(QEasingCurve::OutBack);
    exitButtonAppear->start();

    titleAppear->setStartValue(QRect(lbx,0-lbh,lbw,lbh));
    titleAppear->setEndValue(QRect(lbx,lby,lbw,lbh));
    titleAppear->setDuration(400);
    titleAppear->setEasingCurve(QEasingCurve::OutBack);
    titleAppear->start();
}


void MainWindow::on_ExitButton_clicked()
{
    this->close();
}

void MainWindow::on_ModeButton1_clicked()
{
    if ( modeNumber%2 == 0 ){
        ui->ModeButton1->setText(QApplication::translate("MainWindow", "auto", 0, QApplication::UnicodeUTF8));
        Project::ProjectGame->enableMod(Mania::MOD_AUTO);
    }
    if ( modeNumber%2 == 1 ){
        ui->ModeButton1->setText(QApplication::translate("MainWindow", "manual", 0, QApplication::UnicodeUTF8));
        Project::ProjectGame->disableMod(Mania::MOD_AUTO);
    }
    modeNumber++;
}


void MainWindow::SN_ADD(){
    if(al==0){
        leftBoxDisappear->stop();
        disconnect(LeftBox[((SN+100)+1)%2]->my_splitter,SIGNAL(StartGame()),this,SLOT(InitialGame()));
        LeftBox[((SN+100)+1)%2]->deleteLater();
//            LeftBox[(SN+1)%2]=NULL;
        LeftBox[(SN+100)%2]->show();
        LeftBox[(SN+100)%2]->setGeometry(QRect(lx,ly,lw,lh));
    }
    //   DebugL("");
    al=0;
    //a2=1;
    leftBoxDisappear->setTargetObject(LeftBox[(SN+100)%2]);
//    DebugL("x");
    leftBoxDisappear->setStartValue(QRect(lx,ly,lw,lh));
    leftBoxDisappear->setEndValue(QRect(0-lw,ly,lw,lh));
    leftBoxDisappear->setDuration(400);
    //leftBoxDisappear->setEasingCurve();
    leftBoxDisappear->start(QAbstractAnimation::KeepWhenStopped);
    SN++;
    ST++;
    if (ST>=s.Number) ST = 0;
    if (ST<0) ST = s.Number-1;
    //   DebugL("y")
    LeftBox[(SN+100)%2] = new DifficultyScrollArea(s.songlist[(ST+s.Number+3)%s.Number],this);
    connect(LeftBox[((SN+100))%2]->my_splitter,SIGNAL(StartGame()),this,SLOT(InitialGame()));
    DebugL("y1")
    string place = "assets\\songs\\" + s.songlist[(ST+s.Number+3)%s.Number].fileName;
    place = place + "\\";
    place = place + s.songlist[(ST+s.Number+3)%s.Number].difficultylist[0].audiofilename;
    EdpFile f(*Project::ProjectRoot,place);
    string fullpath = f.getFullPath();
    Project::ProjectGame->loadMusic(fullpath,s.songlist[(ST+s.Number+3)%s.Number].difficultylist[0].previewtime);
}


void MainWindow::SN_SUB(){
    if(al==0){
        leftBoxDisappear->stop();
        disconnect(LeftBox[((SN+100)+1)%2]->my_splitter,SIGNAL(StartGame()),this,SLOT(InitialGame()));
        LeftBox[((SN+100)+1)%2]->deleteLater();
//            LeftBox[(SN+1)%2]=NULL;
        LeftBox[(SN+100)%2]->show();
        LeftBox[(SN+100)%2]->setGeometry(QRect(lx,ly,lw,lh));
        //      LeftBox[(SN+1)%2] = new DifficultyScrollArea
        //       a2 = 0;
    }
//        DebugL("")
    al=0;
    leftBoxDisappear->setTargetObject(LeftBox[(SN+100)%2]);
    leftBoxDisappear->setStartValue(QRect(lx,ly,lw,lh));
    leftBoxDisappear->setEndValue(QRect(0-lw,ly,lw,lh));
    leftBoxDisappear->setDuration(400);
    //leftBoxDisappear->setEasingCurve();
    leftBoxDisappear->start(QAbstractAnimation::KeepWhenStopped);
    SN--;
    ST--;
    if (ST>=s.Number) ST = 0;
    if (ST<0) ST = s.Number-1;
    LeftBox[(SN+100)%2] = new DifficultyScrollArea(s.songlist[(ST+s.Number+3)%s.Number],this);
    connect(LeftBox[((SN+100))%2]->my_splitter,SIGNAL(StartGame()),this,SLOT(InitialGame()));

    string place = "assets\\songs\\" + s.songlist[(ST+s.Number+3)%s.Number].fileName;
    place = place + "\\";
    place = place + s.songlist[(ST+s.Number+3)%s.Number].difficultylist[0].audiofilename;
    EdpFile f(*Project::ProjectRoot,place);
    string fullpath = f.getFullPath();
//    DebugL(fullpath.c_str())
    Project::ProjectGame->loadMusic(fullpath,s.songlist[(ST+s.Number+3)%s.Number].difficultylist[0].previewtime);
//    this->setStyleSheet("background-color:red");
}

void MainWindow::SN_SUB_ANIM1(){
//        DebugL("z")
    al = 1;
    //   if ( a2 == 1 )

    //   LeftBox[(SN+1)%2]=NULL;
//    DebugL("l")
    //   a2 = 1;
    LeftBox[(SN+100)%2]->show();
    LeftBox[(SN+100)%2]->setGeometry(0-lw,ly,lw,lh);
    leftBoxAppear->setTargetObject(LeftBox[(SN+100)%2]);

    leftBoxAppear->setDuration(400);
    leftBoxAppear->setStartValue(QRect(0-lw,ly,lw,lh));
    leftBoxAppear->setEndValue(QRect(lx,ly,lw,lh));
    //leftBoxAppear->setEasingCurve();
    leftBoxAppear->start();
//        DebugL("l")
    disconnect(LeftBox[((SN+100)+1)%2]->my_splitter,SIGNAL(StartGame()),this,SLOT(InitialGame()));
    LeftBox[(SN+101)%2]->deleteLater();
    //           DebugL("d")
}

void MainWindow::InitialGame(){

    leftBoxDisappear01->setTargetObject(LeftBox[(SN+100)%2]);
    leftBoxDisappear01->setPropertyName("geometry");




  //  port = new QHBoxLayout(this) ;
  //  port->addWidget(gameview);

       upButtonDisappear01->setStartValue(QRect(ux,uy,uw,uh));
       upButtonDisappear01->setEndValue(QRect(ux,uy-uh,uw,uh));
       upButtonDisappear01->setDuration(800);
       upButtonDisappear01->setEasingCurve(QEasingCurve::InBack);
       upButtonDisappear01->start();

       modeButtonDisappear01->setStartValue(QRect(mx,my,mw,mh));
       modeButtonDisappear01->setEndValue(QRect(mx,this->height()+mh,mw,mh));
       modeButtonDisappear01->setDuration(800);
       modeButtonDisappear01->setEasingCurve(QEasingCurve::InBack);
       modeButtonDisappear01->start();

       leftBoxDisappear01->setStartValue(QRect(lx,ly,lw,lh));
       leftBoxDisappear01->setEndValue(QRect(0-lw,ly,lw,lh));
       leftBoxDisappear01->setDuration(800);
       //leftBoxDisappear01->setEasingCurve();
       leftBoxDisappear01->start();

       rightBoxDisappear01->setStartValue(QRect(rx,ry,rw,rh));
       rightBoxDisappear01->setEndValue(QRect(this->width()+rw,ry,rw,rh));
       rightBoxDisappear01->setDuration(800);
       rightBoxDisappear01->setEasingCurve(QEasingCurve::InBack);
       rightBoxDisappear01->start();

}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    //Project::ProjectGame->mkeyPressEvent(event);
    QWidget::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    //Project::ProjectGame->mkeyReleaseEvent(event);
    QWidget::keyReleaseEvent(event);
}


void MainWindow::GAMESTART(){
    LeftBox[(SN+100)%2]->close();
    RightBox->close();
    ui->upButton->close();
    ui->ModeButton1->close();
    gameview->show();
    gameview->setFocus();
    gameview->onGameStart();
    Project::ProjectGame->startGame();
}

void MainWindow::GAMEEND(){

    Project::ProjectGame->releaseGame();

    Project::ProjectGame->playNormalMusic();

    gameview->close();
    leftBoxAppear01->setTargetObject(LeftBox[(SN+100)%2]);
    leftBoxAppear01->setPropertyName("geometry");

    ui->upButton->show();
    ui->ModeButton1->show();
    LeftBox[(SN+100)%2]->show();
    RightBox->show();

    upButtonAppear01->setStartValue(QRect(ux,uy-uh,uw,uh));
    upButtonAppear01->setEndValue(QRect(ux,uy,uw,uh));
    upButtonAppear01->setDuration(800);
    upButtonAppear01->setEasingCurve(QEasingCurve::InBack);
    upButtonAppear01->start();

    modeButtonAppear01->setStartValue(QRect(mx,this->height()+mh,mw,mh));
    modeButtonAppear01->setEndValue(QRect(mx,my,mw,mh));
    modeButtonAppear01->setDuration(800);
    modeButtonAppear01->setEasingCurve(QEasingCurve::InBack);
    modeButtonAppear01->start();

    leftBoxAppear01->setStartValue(QRect(0-lw,ly,lw,lh));
    leftBoxAppear01->setEndValue(QRect(lx,ly,lw,lh));
    leftBoxAppear01->setDuration(800);
    //leftBoxAppear01->setEasingCurve();
    leftBoxAppear01->start();

    rightBoxAppear01->setStartValue(QRect(this->width()+rw,ry,rw,rh));
    rightBoxAppear01->setEndValue(QRect(rx,ry,rw,rh));
    rightBoxAppear01->setDuration(800);
    rightBoxAppear01->setEasingCurve(QEasingCurve::InBack);
    rightBoxAppear01->start();
}

