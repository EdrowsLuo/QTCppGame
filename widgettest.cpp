#include "widgettest.h"
#include "shadow.h"

Widgettest::Widgettest(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
{
    //fullscreen = false;
    setFixedSize(800,600);
}

void Widgettest::animate(){
    repaint();
}
Widgettest::~Widgettest()
{

}

void Widgettest::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    QPainterPath path0;
    path0.moveTo(0,100);
    path0.lineTo(1280,100);
    path0.lineTo(1280,600);
    path0.lineTo(0,600);
    painter.setBrush(Qt::white);
    painter.drawPath(path0);

    Shadow drawshadow;
    drawshadow.draw(event,&painter);
    painter.end();
}
