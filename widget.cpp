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
#include "addcas.h"
#include "rankingpic.h"
//#include "testtest.h"
#include "Util.h"
#include "keys.h"
using namespace edp;
using namespace nso;

Widget::Widget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
    ,
    ui(new Ui::Widget)
{
    //BG1 = new RankingBG(&manager);
    ui->setupUi(this);
    //this->setFixedSize(720*16/9,720);
   /* EdpFile *osuFile = new EdpFile(
           "D:\\QT\\wj\\MyBKG\\qt_bb\\data\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [4K Lv.4].osu"
            //"D:\\QT\\wj\\MyBKG\\qt_bb\\data\\356253 ginkiha - Borealis\\ginkiha - Borealis ([ A v a l o n ]) [CS' ADVANCED].osu"
            //"D:\\QT\\wj\\MyBKG\\qt_bb\\data\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [Starry's 4K Lv.15].osu"
            );*/
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
    timer->start(12);
    //Game->linkKeyInput(keyPipee);
    //Game->runGame();
    mGameHolder = Project::ProjectGame;

    //mGameHolder->enableMod(Mania::MOD_AUTO);
    //mGameHolder ->loadGame(osuFile);

    //mGameHolder->getGame()->runGame();
    //mGameHolder->getGame()->getSongChannel()->seekTo(102000);
    esc= false;
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
    //DebugL("")
    QPainter painter(this);
    /*if(Game->updateTime()){
        Game->update();
    }*/
    mGameHolder->update();

    if(mGameHolder->EscPressed){
        //DebugL("")
        esc=true;
        timesup=util::currentTimeMS();
    }

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
    if (Game->getFrameTime() < Game->getSongChannel()->length() + 2550) {
        //背景轨道绘制
        draw2.judge = KeyNum;
        EdpFile f(*Game->getSetDirectory(),Game->getOsuBeatmap()->BackgroundFile);
        draw1.set(f.getFullPath());
        draw1.draw(event, &painter);
        draw2.draw(event, &painter);
        drawkey0.judge = KeyNum;
        int t = Game->getPlayingData()->getScore()->getScore();
        Scorenow = Game->getPlayingData()->getScore()->getScore();
        //Note 与 HOLDER
        ForEachLong(Game->getDrawdata()->getDatas(), itr, vector<ManiaDrawdataNode>::iterator) {
            if (itr->type == ManiaDrawdata::HOLD) {
                draw11.set(itr->line, itr->position, itr->endposition, KeyNum);
                draw11.draw(event, &painter);
            } else {
                draw10.set(itr->line, itr->position, KeyNum);
                draw10.draw(event, &painter);
            }
        }

        //Combo与分数统计与动画变化
        if (Scorenow == Scorepre) {
            for (int j = 6; j >= 0; j--) {
                Score[j] = t - t / 10 * 10;
                t = t / 10;
                draw3.set(512 + 36 * j, 0, 36, 60, Score[j]);
                draw3.draw(event, &painter);
            }
        } else {
            for (int j = 6; j >= 0; j--) {
                Score[j] = t - t / 10 * 10;
                t = t / 10;
                draw3.set(491 + 42 * j, 0, 42, 70, Score[j]);
                draw3.draw(event, &painter);
            }
        }
        if (Scorenow == Scorepre) {
            drawcombo.set(Game->getPlayingData()->getScore()->Combo,
                              false);//Game->getPlayingData()->getScore()->Combo
            //
            drawcombo.draw(event, &painter);
        } else {
            drawcombo.set(Game->getPlayingData()->getScore()->Combo, true);
            //
            drawcombo.draw(event, &painter);
        }

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
        if (KeyNum == 1) {
            //drawkey0.setjudge(KeyNum);;
            for (int i = 0; i < 4; i++) {
                Combonow = Game->getPlayingData()->getScore()->Combo;
                drawkey0.setKeyjudge(Game->getPlayingData()->getKeys()[i]->isPressed());//
                drawkey0.setnum(i);
                drawkey0.draw(event, &painter);
                if (Game->getPlayingData()->getKeys()[i]->isPressed()) {
                    if (Scorenow != Scorepre) {
                        //if (Combopre==Combonow){
                        drawjudge.set(Game->getPlayingData()->getScore()->RecentScore, false);
                        drawjudge.draw(event, &painter);
                    } else {
                        drawjudge.set(Game->getPlayingData()->getScore()->RecentScore, true);
                        drawjudge.draw(event, &painter);
                    }
                    //}
                }
            }
            Combopre = Game->getPlayingData()->getScore()->Combo;
        }
        if (KeyNum == 0) {
            //drawkey0.setjudge(KeyNum);
            for (int j = 0; j < 7; j++) {
                Combonow = Game->getPlayingData()->getScore()->Combo;
                drawkey0.setKeyjudge(Game->getPlayingData()->getKeys()[j]->isPressed());//
                drawkey0.setnum(j);
                drawkey0.draw(event, &painter);
                if (Game->getPlayingData()->getKeys()[j]->isPressed()) {
                    if (Scorenow != Scorepre) {
                        //if (Combopre==Combonow){
                        drawjudge.set(Game->getPlayingData()->getScore()->RecentScore, false);
                        drawjudge.draw(event, &painter);
                    } else {
                        drawjudge.set(Game->getPlayingData()->getScore()->RecentScore, true);
                        drawjudge.draw(event, &painter);
                    }
                    //}
                }
            }
            Combopre = Game->getPlayingData()->getScore()->Combo;
        }

        Scorepre = Game->getPlayingData()->getScore()->getScore();

        //节奏线
        ForEachLong(*Game->getDrawdata()->getBeatsAvalibe(), itr, vector<double>::iterator) {
            drawrhy.set(*itr);
            drawrhy.draw(event, &painter);
        }

        //阴影
        drawshadow.draw(event, &painter);

        //进度条
        drawPB.set(Game->getFrameTime() / Game->getSongChannel()->length());
        drawPB.draw(event, &painter);
    }//im
    //结算界面绘制
    double timelong = Game->getSongChannel()->length();
    //MyScore draw11(270,90,36,60,0);
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
            if (timesub>=(3050+300*i)){
                if (timesub<=3350+300*i){
                    pixmapgh.set(100.0,120+66*i-33*(1-(3350+300*i-timesub)/300),144,66*(1-(3350+300*i-timesub)/300),5-i);
                    //pixmapgh.get();
                    pixmapgh.draw(event,&painter);
                }
                else {
                    //painter.drawPixmap(,pixmapjs[i]);
                    pixmapgh.set(100.0,87+66.0*i,144,66,5-i);
                    //pixmapgh.get();
                    pixmapgh.draw(event,&painter);
                }
            }
        }
        if(timesub>4850&&timesub<=5150){
            pixcas.set(100,530-36*(1-(5150-timesub)/300),230,72*(1-(5150-timesub)/300),1);
            pixcas.draw(event,&painter);
        }
        else if (timesub>5150){
            pixcas.set(100,494,230,72,1);
            pixcas.draw(event,&painter);
        }
        if(timesub>5150&&timesub<=5450){
            pixcas.set(630,537-32*(1-(5450-timesub)/300),351,64*(1-(5450-timesub)/300),2);
            pixcas.draw(event,&painter);
        }
        else if (timesub>5450){
            pixcas.set(630,505,351,64,2);
            pixcas.draw(event,&painter);
        }
        if(timesub>5450&&timesub<=5750){
            pixcas.set(100,610-36*(1-(5750-timesub)/300),230,72*(1-(5750-timesub)/300),3);
            pixcas.draw(event,&painter);
        }
        else if (timesub>5750){
            pixcas.set(100,574,230,72,3);
            pixcas.draw(event,&painter);
        }
        //翻动数字效果
        if (timesub>5750&&timesub<5950){
            for (int i=0;i<6;i++){
                int t=Game->getPlayingData()->getScore()->HitCounter[5-i];
                drawfirst.set(414,120+66*i-30*(1-(5950-timesub)/200),36,60*(1-(5950-timesub)/200),t-t/10*10);
                drawfirst.draw(event,&painter);
            }
        }
        else if (timesub>5950){
            for (int i=0;i<6;i++){
                int t=Game->getPlayingData()->getScore()->HitCounter[5-i];
                drawfirst.set(414,90+66*i,36,60,t-t/10*10);
                drawfirst.draw(event,&painter);
            }
        }
        if (timesub>5950&&timesub<6150){
            for (int i=0;i<6;i++){
                int t=Game->getPlayingData()->getScore()->HitCounter[5-i];
                drawfirst.set(378,120+66*i-30*(1-(6150-timesub)/200),36,60*(1-(6150-timesub)/200),t/10-t/100*10);
                drawfirst.draw(event,&painter);
            }
        }
        else if (timesub>6150){
            for (int i=0;i<6;i++){
                int t=Game->getPlayingData()->getScore()->HitCounter[5-i];
                drawfirst.set(378,90+66*i,36,60,t/10-t/100*10);
                drawfirst.draw(event,&painter);
            }
        }
        if (timesub>6150&&timesub<6350){
            for (int i=0;i<6;i++){
                int t=Game->getPlayingData()->getScore()->HitCounter[5-i];
                drawfirst.set(342,120+66*i-30*(1-(6350-timesub)/200),36,60*(1-(6350-timesub)/200),t/100-t/1000*10);
                drawfirst.draw(event,&painter);
            }
        }
        else if (timesub>6350){
            for (int i=0;i<6;i++){
                int t=Game->getPlayingData()->getScore()->HitCounter[5-i];
                drawfirst.set(342,90+66*i,36,60,t/100-t/1000*10);
                drawfirst.draw(event,&painter);
            }
        }
        if (timesub>6350&&timesub<6550){
            for (int i=0;i<6;i++){
                int t=Game->getPlayingData()->getScore()->HitCounter[5-i];
                drawfirst.set(306,120+66*i-30*(1-(6550-timesub)/200),36,60*(1-(6550-timesub)/200),t/1000);
                drawfirst.draw(event,&painter);
            }
        }
        else if (timesub>6550){
            for (int i=0;i<6;i++){
                int t=Game->getPlayingData()->getScore()->HitCounter[5-i];
                drawfirst.set(306,90+66*i,36,60,t/1000);
                drawfirst.draw(event,&painter);
            }
        }
        int s=Game->getPlayingData()->getScore()->MaxCombo;
        //DebugI(s)
        /*if (timesub>6550&&timesub<6850){
            for (int i=0;i<4;i++){

                MaxCombo[i]=s-s/10*10;
                MyScore drawfirst(494-36*i,530-30*(1-(6850-timesub)/300),36,60*(1-(6850-timesub)/300),MaxCombo[i]);
                drawfirst.draw(event,&painter);
                s=s/10;
            }
        }
        else if (timesub>6850){
            for (int i=0;i<4;i++){

                MaxCombo[i]=s-s/10*10;
                MyScore drawfirst(494-36*i,500,36,60,MaxCombo[i]);
                drawfirst.draw(event,&painter);
                s=s/10;
            }
        }*/
        for (int i=0;i<4;i++){
        if (Game->getFrameTime()-6550>100*i){
            MaxCombo[i]=s%10;
            if (timesub>6550+i*100&&timesub<6650+i*100){
                drawfirst.set(494-36*i,535-30*(1-(6650+i*100-timesub)/100),36,60*(1-(6650+i*100-timesub)/100),MaxCombo[i]);
                drawfirst.draw(event,&painter);
            }
            else if(timesub>6650+100*i){
                drawfirst.set(494-36*i,505,36,60,MaxCombo[i]);
                drawfirst.draw(event,&painter);
            }
            s=s/10;
        }
        }
        double f = Game->getPlayingData()->getScore()->getAccuracy() * 10000;
        int accuracy = (int)f;
        if (timesub > 6850){
            QPixmap pixmapp;
            pixmapp.load(nso::Project::fromRootQ("assets\\image\\default-percent.png"));
            painter.drawPixmap(1200,530,22.5,22.5,pixmapp);
        }
        if (f == 1){
        if (timesub>7050){
            QPixmap pixmappp;
            pixmappp.load(nso::Project::fromRootQ("assets\\image\\point.png"));
            painter.drawPixmap(1114,545,4,4,pixmappp);
        }
        for (int i=0;i<4;i++){
        if (Game->getFrameTime()-6850>100*i){
            MaxCombo[i]=accuracy-accuracy/10*10;
            if (timesub>6850+i*100&&timesub<6950+i*100){
                drawfirst.set(1160-40*i,535-30*(1-(6950+i*100-timesub)/100),36,60*(1-(6950+i*100-timesub)/100),MaxCombo[i]);
                drawfirst.draw(event,&painter);
            }
            else if(timesub>6950+100*i){
                drawfirst.set(1160-40*i,505,36,60,MaxCombo[i]);
                drawfirst.draw(event,&painter);
            }
            accuracy=accuracy/10;
        }
        }
        }
        else{
            accuracy = 1000;
            if (timesub>7050){
                QPixmap pixmappp;
                pixmappp.load(nso::Project::fromRootQ("assets\\image\\point.png"));
                painter.drawPixmap(1154,545,4,4,pixmappp);
            }
            for (int i=0;i<4;i++){
            if (Game->getFrameTime()-6850>100*i){
                MaxCombo[i]=accuracy-accuracy/10*10;
                if (timesub>6850+i*100&&timesub<6950+i*100){
                    drawfirst.set(1160-40*i,535-30*(1-(6950+i*100-timesub)/100),36,60*(1-(6950+i*100-timesub)/100),MaxCombo[i]);
                    drawfirst.draw(event,&painter);
                }
                else if(timesub>6950+100*i){
                    drawfirst.set(1160-40*i,505,36,60,MaxCombo[i]);
                    drawfirst.draw(event,&painter);
                }
                accuracy=accuracy/10;
            }
            }
        }
        int o=Game->getPlayingData()->getScore()->getScore();
        for (int i=0;i<7;i++){
        if (Game->getFrameTime()-7350>150*i){
            Totalscore[i]=o-o/10*10;
            if (timesub>7350+i*150&&timesub<7500+i*150){
                drawfirst.set(600-36*i,620-30*(1-(7500+i*150-timesub)/150),36,60*(1-(7500+i*150-timesub)/150),Totalscore[i]);
                drawfirst.draw(event,&painter);
            }
            else if(timesub>7500+150*i){
                drawfirst.set(600-36*i,590,36,60,Totalscore[i]);
                drawfirst.draw(event,&painter);
            }
            o=o/10;
        }
        }
        if (timesub>8400&&timesub<9000){
            drawR.set(1-(9000-timesub)/600,sqrt(1+(9000-timesub)/600),Game->getPlayingData()->getScore()->getRanking());
            drawR.draw(event,&painter);
        }
        else if (timesub >9000){
            drawR.set(1,1,Game->getPlayingData()->getScore()->getRanking());
            drawR.draw(event,&painter);
        }
    }
    if (esc){
        QPainterPath pathend;
        pathend.moveTo(0,0);
        pathend.lineTo(1280,0);
        pathend.lineTo(1280,720);
        pathend.lineTo(0,720);
        int sub = static_cast<int>(util::currentTimeMS() - timesup);
        if (sub<=600){
            painter.setBrush(QColor(40,44,53,sub*255/600));
            painter.drawPath(pathend);
        }
        else if (sub>600){
            painter.setBrush(QColor(40,44,53,255));
            painter.drawPath(pathend);
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
    //Game->getPlayingData()->getScore()->getRanking();
    painter.end();

    mGameHolder->endUpdate();
}
