#include "widget.h"
#include "ui_widget.h"
#include "background.h"
#include "tracke.h"
#include "mycombo.h"
#include "EdpBass.h"

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
    keyPipe = new QTKeyPipe();
    //DebugL("")
    keyPipe->setTimer(Game->getSongChannel());
    //DebugL("")
    QTimer *timer=new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(animate()));
    timer->start(20);
    Game->linkKeyInput(keyPipe);
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


void Widget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    Game->update();
   // static
    double wid = rect().width();
    //static
    double hei = rect().height();
    painter.scale(wid/1280,hei/720);

    BackGround draw1;
    trackE draw2(0);
    draw1.draw(event,&painter);
    draw2.draw(event,&painter);
    Keys drawkey0;
    for (int i=0;i<4;i++){
        drawkey0.setKeyjudge(Game->getPlayingData()->getKeys()[i]->isPressed());//
        drawkey0.setnum(i);
        drawkey0.draw(event,&painter);

    }


    /*DrawTextW draw3(512,0,36,60,0);
    draw3.draw(event,&painter);
    DrawTextW draw4(548,0,36,60,0);
    draw4.draw(event,&painter);
    DrawTextW draw5(584,0,36,60,0);
    draw5.draw(event,&painter);
    DrawTextW draw6(620,0,36,60,0);
    draw6.draw(event,&painter);
    DrawTextW draw7(656,0,36,60,0);
    draw7.draw(event,&painter);
    DrawTextW draw8(692,0,36,60,0);
    draw8.draw(event,&painter);
    DrawTextW draw9(728,0,36,60,0);
    draw9.draw(event,&painter);*/

    //Testtest test();
}
