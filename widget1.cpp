#include "widget1.h"
#include "shadow.h"
Widget1::Widget1(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
    ,
    ui(new Ui::Widget1)
{
}
void Widget1::paintEvent(QPaintEvent *event){
    Shadow drawshadow;
    drawshadow.draw(event,&painter);
}
