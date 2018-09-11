#include "widget.h"
#include "ui_widget.h"
#include "background.h"
#include "tracke.h"
#include "mycombo.h"
#include "EdpBass.h"
#include "ManiaRuleset.h"
#include "myscore.h"
#include "squaredown.h"
#include "squaredownh.h"
#include "defext.h"
//#include "testtest.h"
#include "keys.h"
using namespace edp;
using namespace nso;

Widget::Widget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
    ,
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    EdpFile *osuFile = new EdpFile(
           "D:\\QT\\wj\\MyBKG\\qt_bb\\data\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [4K Lv.4].osu"
            //"D:\\QT\\wj\\MyBKG\\qt_bb\\data\\356253 ginkiha - Borealis\\ginkiha - Borealis ([ A v a l o n ]) [CS' ADVANCED].osu"
            //"D:\\QT\\wj\\MyBKG\\qt_bb\\data\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [Starry's 4K Lv.15].osu"
            );
    Game = new ManiaGame(osuFile,new ManiaSetting());
    //DebugL("")
    Game->prepareGame();
    //DebugL("")
    keyPipee = new QTKeyPipe();
    //DebugL("")
    keyPipee->setTimer(Game->getSongChannel());
    //DebugL("")
    QTimer *timer=new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(animate()));
    timer->start(20);
    Game->linkKeyInput(keyPipee);
    Game->runGame();

    //EdpBassChannel *cha = new EdpBassChannel("D:\\QT\\wj\\MyBKG\\data\\324288 xi - ANiMA\\anima.mp3");
    //cha->play();
}

void Widget::animate(){
    repaint();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::keyPressEvent(QKeyEvent *event){
    if (event->isAutoRepeat()){
        return;
    }

    //this->keyPipe;

    //if (keyPipe != NULL){
        keyPipee->keyPressEvent(event);
    //}
}

void Widget::keyReleaseEvent(QKeyEvent *event){
    if (event->isAutoRepeat()){
        return;
    }
    //if (keyPipe != NULL){
        keyPipee->keyReleaseEvent(event);
    //}
}

void Widget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    if(Game->updateTime()){
        Game->update();
    }

    KeyNum=1;
    NorH=false;
   // static
    double wid = rect().width();
    //static
    double hei = rect().height();
    painter.scale(wid/1280,hei/720);

    BackGround draw1;
    trackE draw2(KeyNum);
    draw1.draw(event,&painter);
    draw2.draw(event,&painter);
    Keys drawkey0(KeyNum);


    MyScore draw3(512,0,36,60,0);
    draw3.draw(event,&painter);
    MyScore draw4(548,0,36,60,0);
    draw4.draw(event,&painter);
    MyScore draw5(584,0,36,60,0);
    draw5.draw(event,&painter);
    MyScore draw6(620,0,36,60,0);
    draw6.draw(event,&painter);
    MyScore draw7(656,0,36,60,0);
    draw7.draw(event,&painter);
    MyScore draw8(692,0,36,60,0);
    draw8.draw(event,&painter);
    MyScore draw9(728,0,36,60,0);
    draw9.draw(event,&painter);


    ForEachLong(Game->getDrawdata()->getDatas(),itr,vector<ManiaDrawdataNode>::iterator){
        if (itr->type != ManiaDrawdata::HOLD){
            SquareDownH draw11(itr->line,itr->position,itr->endposition,KeyNum);
            draw11.draw(event,&painter);
        }
        else {
            SquareDown draw10(itr->line,itr->position,KeyNum);
            draw10.draw(event,&painter);
        }
    }
    if (KeyNum==1){
        //drawkey0.setjudge(KeyNum);;
    for (int i=0;i<4;i++){
        drawkey0.setKeyjudge(Game->getPlayingData()->getKeys()[i]->isPressed());//
        drawkey0.setnum(i);
        drawkey0.draw(event,&painter);
        }
    }
    if (KeyNum==0){
        //drawkey0.setjudge(KeyNum);
        for (int j=0;j<7;j++){
        drawkey0.setKeyjudge(Game->getPlayingData()->getKeys()[j]->isPressed());//
        drawkey0.setnum(j);
        drawkey0.draw(event,&painter);
        }
    }

    //Testtest test();
}
