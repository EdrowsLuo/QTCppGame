#ifndef WIDGET_H
#define WIDGET_H

#include <QGLWidget>
#include <QWidget>
#include <QPainter>
#include "ManiaRuleset.h"
#include <KeyIO.h>
#include "BeatmapDecoder.h"
#include "EdpFile.h"
#include <QTimer>
#include "pixmapmanager.h"
#include "rankingbg.h"
#include "background.h"
#include "tracke.h"
#include "keys.h"
#include "squaredownh.h"
#include "squaredown.h"
#include "myscore.h"
#include "mycombo.h"
#include "judgescore.h"
#include "rhythmline.h"
#include "shadow.h"
#include "progressbar.h"
#include "judgescore2.h"
#include "addcas.h"
#include "rankingpic.h"

using namespace edp;
using namespace nso;
namespace Ui {
    class Widget;
}

#define USING_GL

#ifdef USING_GL
typedef QGLWidget Renderer;
#else
typedef QWidget Renderer;
#endif

class Widget : public Renderer
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *event);
    void onGameStart();
public slots:
    void animate();

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

signals:
    void GameEnd();

private:
    Ui::Widget *ui;
    int Score[7];
    ManiaGame *Game;
    QTKeyPipe *keyPipee;
    int KeyNum;
    bool NorH,endjudge;
    GameHolder *mGameHolder;
    int Scorepre,Scorenow;
    int Combopre,Combonow;
    //RankingBG *BG1;
    Pixmapmanager manager;
    int Comborecord,ssr;
    double timerecord;
    int t,tranjudge;
    int MaxCombo[4];
    int Totalscore[7];
    bool esc;
    long long int timesup;
    double tranj;

    BackGround draw1;
    trackE draw2;
    Keys drawkey0;
    SquareDownH draw11;
    SquareDown draw10;
    MyScore draw3;
    MyCombo drawcombo;
    judgeScore drawjudge;
    rhythmLine drawrhy;
    Shadow drawshadow;
    ProgressBar drawPB;
    judgeScore2 pixmapgh;
    AddCAS pixcas;
    MyScore drawfirst;
    Rankingpic drawR;
    Pressesc drawpress;
    double timestarts;
};

#endif // WIDGET_H
