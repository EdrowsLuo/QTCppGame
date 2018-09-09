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
    ui->setupUi(this);

    view = new TestView(this);


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(view, 0, 0);
    layout->addWidget(ui->pushButton, 1, 0);
    layout->addWidget(ui->pushButton_2, 2, 0);
    layout->addWidget(ui->horizontalSlider, 3, 0);
    setLayout(layout);

    //QMetaObject::connectSlotsByName(this);

    {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), view, SLOT(animate()));
        timer->start(5);
    }
    {
        /*QTimer *timer2 = new QTimer(this);
        connect(timer2, SIGNAL(timeout()), view, SLOT(test()));
        timer2->start(2);*/
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    if (view->Game->running()){
        view->Game->pauseGame();
    } else {
        view->Game->runGame();
    }
    Debug("clicked");
    //view->Game->pauseGame();
    //view->Game->runGame();
}

void Dialog::on_pushButton_2_clicked()
{
    view->Game->reset();
    view->Game->runGame();
}

void Dialog::animate() {

}

void Dialog::on_horizontalSlider_valueChanged(int value)
{
    view->Game->getSongChannel()->setVolume(value / 100.0f);
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