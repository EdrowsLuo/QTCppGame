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
using namespace edp;
using namespace nso;
namespace Ui {
    class Widget1;
}

class Widget1 : public QGLWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *event);
    Ui::Widget *ui;
}


#endif // WIDGET_H
