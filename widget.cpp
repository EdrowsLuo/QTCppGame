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
#include "shadow.h"
#include "progressbar.h"
#include "rhythmline.h"
#include "judgescore.h"
#include "calscore.h"
#include "rankingbg.h"
#include "judgescore2.h"
//#include "testtest.h"
#include "keys.h"
using namespace edp;
using namespace nso;

Widget::Widget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
    ,
    ui(new Ui::Widget)
{
    //BG1 = new RankingBG(&manager);
    ui->setupUi(this);
    this->setFixedSize(720*16/9,720);
    EdpFile *osuFile = new EdpFile(
           //"D:\\QT\\wj\\MyBKG\\qt_bb\\data\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [4K Lv.4].osu"
            //"D:\\QT\\wj\\MyBKG\\qt_bb\\data\\356253 ginkiha - Borealis\\ginkiha - Borealis ([ A v a l o n ]) [CS' ADVANCED].osu"
            //"D:\\QT\\wj\\MyBKG\\qt_bb\\data\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [Starry's 4K Lv.15].osu"
            "D:\\QT\\wj\\QTCppGame\\assets\\songs\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [Ryosaka's 7K Lv.19].osu"
            );
    //Game = new ManiaGame(osuFile,new ManiaSetting());
    //DebugL("")
    //Game->prepareGame();
    //DebugL("")
    //keyPipee = new QTKeyPipe();
    //DebugL("")
    //keyPipee->setTimer(Game->getSongChannel());
    //DebugL("")
    QTimer *timer=new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(animate()));
    timer->start(0.1);
    //Game->linkKeyInput(keyPipee);
    //Game->runGame();
    mGameHolder = Project::ProjectGame;

    mGameHolder->enableMod(Mania::MOD_AUTO);
    mGameHolder ->loadGame(osuFile);

    mGameHolder->getGame()->runGame();
    mGameHolder->getGame()->getSongChannel()->seekTo(102000);
}

void Widget::animate(){
    repaint();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::keyPressEvent(QKeyEvent *event){
   mGameHolder->mkeyPressEvent(event);
}

void Widget::keyReleaseEvent(QKeyEvent *event){
    mGameHolder->mkeyReleaseEvent(event);
}

void Widget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    /*if(Game->updateTime()){
        Game->update();
    }*/
    mGameHolder->update();
    ManiaGame *Game = mGameHolder->getGame();

    if (Game->getOsuBeatmap()->getKeys()==4){
        KeyNum=1;
    }
    else {
        KeyNum=0;
    }
    NorH=false;
   // static
    double wid = rect().width();
    //static
    double hei = rect().height();
    painter.scale(wid/1280,hei/720);

    //背景轨道绘制
    BackGround draw1;
    trackE draw2(KeyNum);
    draw1.draw(event,&painter);
    draw2.draw(event,&painter);
    Keys drawkey0(KeyNum);
    int t=Game->getPlayingData()->getScore()->getScore();
    Scorenow=Game->getPlayingData()->getScore()->getScore();
    //Note 与 HOLDER
    ForEachLong(Game->getDrawdata()->getDatas(),itr,vector<ManiaDrawdataNode>::iterator){
        if (itr->type == ManiaDrawdata::HOLD){
            SquareDownH draw11(itr->line,itr->position,itr->endposition,KeyNum);
            draw11.draw(event,&painter);
        }
        else {
            SquareDown draw10(itr->line,itr->position,KeyNum);
            draw10.draw(event,&painter);
        }
    }

    //Combo与分数统计与动画变化
    if (Scorenow==Scorepre){
        for (int j=6;j>=0;j--){
            Score[j]=t-t/10*10;
            t=t/10;
            MyScore draw3(512+36*j,0,36,60,Score[j]);
            draw3.draw(event,&painter);
        }
    }
    else {
        for (int j=6;j>=0;j--){
            Score[j]=t-t/10*10;
            t=t/10;
            MyScore draw3(491+42*j,0,42,70,Score[j]);
            draw3.draw(event,&painter);
        }
    }
    if (Scorenow==Scorepre){
        MyCombo drawcombo(Game->getPlayingData()->getScore()->Combo,false);//Game->getPlayingData()->getScore()->Combo
        //
        drawcombo.draw(event,&painter);
    }
    else{
        MyCombo drawcombo(Game->getPlayingData()->getScore()->Combo,true);
        //
        drawcombo.draw(event,&painter);
    }
    Scorepre=Game->getPlayingData()->getScore()->getScore();

    /*MyScore draw3(512,0,36,60,0);
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
    draw9.draw(event,&painter);*/


    //按压效果与Combo动态
    if (KeyNum==1){
        //drawkey0.setjudge(KeyNum);;
    for (int i=0;i<4;i++){
        Combonow=Game->getPlayingData()->getScore()->Combo;
        drawkey0.setKeyjudge(Game->getPlayingData()->getKeys()[i]->isPressed());//
        drawkey0.setnum(i);
        drawkey0.draw(event,&painter);
        /*if(Game->getPlayingData()->getKeys()[i]->isPressed()){
            if (Combopre==Combonow){
                judgeScore draw12(Game->getPlayingData()->getScore()->RecentScore,false);
                draw12.draw(event,&painter);
            }
            else {
                judgeScore draw12(Game->getPlayingData()->getScore()->RecentScore,true);
                draw12.draw(event,&painter);
            }

        }*/

        }
        Combopre=Game->getPlayingData()->getScore()->Combo;
    }
    if (KeyNum==0){
        //drawkey0.setjudge(KeyNum);
        for (int j=0;j<7;j++){
        Combonow=Game->getPlayingData()->getScore()->Combo;
        drawkey0.setKeyjudge(Game->getPlayingData()->getKeys()[j]->isPressed());//
        drawkey0.setnum(j);
        drawkey0.draw(event,&painter);
        if(Game->getPlayingData()->getKeys()[j]->isPressed()){
            if (Combopre==Combonow){
                judgeScore drawjudge(Game->getPlayingData()->getScore()->RecentScore,false);
                drawjudge.draw(event,&painter);
            }
            else {
                judgeScore drawjudge(Game->getPlayingData()->getScore()->RecentScore,true);
                drawjudge.draw(event,&painter);
            }

        }
        }
        Combopre=Game->getPlayingData()->getScore()->Combo;
    }


    //节奏线
    ForEachLong(*Game->getDrawdata()->getBeatsAvalibe(),itr,vector<double>::iterator){
        rhythmLine drawrhy(*itr);
        drawrhy.draw(event,&painter);
    }

    //阴影
    Shadow drawshadow;
    drawshadow.draw(event,&painter);

    //进度条
    ProgressBar drawPB(Game->getFrameTime()/Game->getSongChannel()->length());
    drawPB.draw(event,&painter);

    //结算界面绘制
    double timelong = Game->getSongChannel()->length();
    if ((Game->getFrameTime())>timelong){
        double timepre = Game->getFrameTime();
        double timesub = timepre-timelong;
        QPainterPath pathbb;
        pathbb.moveTo(0,0);
        pathbb.lineTo(1280,0);
        pathbb.lineTo(1280,720);
        pathbb.lineTo(0,720);
        if (timesub<=2550){
            painter.setBrush(QColor(40,44,53,timesub/10));
        }
        else {
            painter.setBrush(QColor(40,44,53,255));
        }
        painter.drawPath(pathbb);
        //judgeScore2 pixmapjs[6];
        for (int i=0;i<=5;i++){
            //pixmapjs[i].load(scorej[5-i]);
            if (timesub>=(3050+500*i)){
                if (timesub<=3550+500*i){
                    judgeScore2 pixmapgh(100.0,120+60*i-25*(1-(3550+500*i-timesub)/500),90.0,50*(1-(3550+500*i-timesub)/500),5-i);
                    //pixmapgh.get();
                    pixmapgh.draw(event,&painter);
                }
                else {
                    //painter.drawPixmap(,pixmapjs[i]);
                    judgeScore2 pixmapgh(100.0,95.0+60.0*i,90.0,50.0,5-i);
                    //pixmapgh.get();
                    pixmapgh.draw(event,&painter);
                }
            }
        }

    }

 //   if()
    //Game->getPlayingData()->getScore()->RecentScore
    //MyCombo drawcombo(Game->getPlayingData()->getScore()->Combo,false);
    //
    //drawcombo.draw(event,&painter);
    //当前帧时间Game->getFrameTime();

    //分数Game->getPlayingData()->getScore()->getScore();
    //节奏Game->Drawdata->getBeatsAvalibe();
    //Testtest test();
    painter.end();
}
