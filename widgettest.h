#ifndef WIDGETTEST_H
#define WIDGETTEST_H

#include <QWidget>
#include <QGLWidget>
#include <QPainter>
class Widgettest : public QGLWidget
{
    Q_OBJECT
public:
    explicit Widgettest(QWidget *parent = 0);
    ~Widgettest();
    void paintEvent(QPaintEvent *event);
public slots:
    void animate();
                              // «∑Ò»´∆¡œ‘ æ
};

#endif
