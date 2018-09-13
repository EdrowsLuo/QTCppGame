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
using namespace edp;
using namespace nso;
namespace Ui {
    class Widget;
}

class Widget : public QGLWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *event);
public slots:
    void animate();
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::Widget *ui;
    int Score[7];
    ManiaGame *Game;
    QTKeyPipe *keyPipee;
    int KeyNum;
    bool NorH;
    GameHolder *mGameHolder;
    int Scorepre,Scorenow;
    int Combopre,Combonow;
    //RankingBG *BG1;
    Pixmapmanager manager;

};

#endif // WIDGET_H
