#include "dialog.h"
#include "ui_dialog.h"
#include "TestView.h"
#include <QKeyEvent>
#include <QTimer>
#include <QtGui>

#include <string>
#include <sstream>

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    //ui->setupUi(this);

    view = new TestView(this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(view, 0, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), view, SLOT(animate()));
    timer->start(5);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{

}

void Dialog::on_pushButton_2_clicked()
{

}

void Dialog::animate() {

}

void Dialog::on_horizontalSlider_valueChanged(int value)
{

}

void Dialog::on_progressBar_valueChanged(int value)
{

}

void Dialog::on_pushButton_4_clicked()
{

}


void Dialog::keyPressEvent(QKeyEvent *event) {
    view->mkeyPressEvent(event);
}

void Dialog::keyReleaseEvent(QKeyEvent *event) {
    view->mkeyReleaseEvent(event);
}