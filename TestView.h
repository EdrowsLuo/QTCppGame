//
// Created by admin on 2018/9/6.
//

#ifndef QT_BB_TESTVIEW_H
#define QT_BB_TESTVIEW_H

#include <QWidget>
#include <ManiaRuleset.h>
#include <KeyIO.h>
#include <EdpBass.h>
#include "Beatmap.h"

#include <QGLWidget>

using namespace nso;
using namespace edp;


class TestView : public QGLWidget {
    Q_OBJECT
public:

    explicit TestView(QWidget *parent);

public slots:
    void animate();
    void test();

protected:
    void paintEvent(QPaintEvent *event);

public:
    virtual void mkeyPressEvent(QKeyEvent *event);
    virtual void mkeyReleaseEvent(QKeyEvent *event);

public:
    /*EdpBassChannel *channel;

    KeyFrame *frame;
    KeyHolder *holder;

    ManiaPlaytimeData *playtimeData;

    Beatmap *beatmap;

    ManiaDrawdata *drawdata;*/

    //GameHolder *mGameHolder;

};


#endif //QT_BB_TESTVIEW_H
