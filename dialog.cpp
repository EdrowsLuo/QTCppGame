#include "dialog.h"
#include "ui_dialog.h"
#include <QKeyEvent>
#include <QTimer>

#include <string>
#include <sstream>

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    string songpath = "D:\\Qt\\code\\qt_bb\\data\\433128 Yui Sakakibara - Koigokoro to Beat!\\PURELYCATION.mp3";
            //"D:\\Qt\\code\\qt_bb\\data\\324288 xi - ANiMA\\anima.mp3";
    channel = new EdpBassChannel(songpath);
    keyPipe = new QTKeyPipe();
    keyPipe->setTimer(channel);
    frame = new KeyFrame(keyPipe, channel);
    holder = new KeyHolder();
    frame->registerHolder(Qt::Key_A,holder);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(15);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    channel->play();
}

void Dialog::on_pushButton_2_clicked()
{
    channel->pause();
}

void Dialog::animate() {
    /*frame->update(10000);

    frame->endFrmae();*/

    frame->update();

    stringstream ss;
    ss << "press : " << holder->isPressed() << "  time: " << holder->getTime();
    ui->label->setText(QString::fromUtf8(ss.str().c_str()));

    frame->endFrame();
}

void Dialog::on_horizontalSlider_valueChanged(int value)
{
    stringstream ss;
    ss << "seek to " << value;
    qDebug(ss.str().c_str());

    channel->seekTo(value * 1000);
}

void Dialog::on_progressBar_valueChanged(int value)
{
    stringstream ss;
    ss << "seek to " << value;
    qDebug(ss.str().c_str());

    channel->seekTo(value * 1000);
}

void Dialog::on_pushButton_4_clicked()
{
    /*stringstream ss;
    ss << "pos : " << channel->playingTime();
    ui->label->setText(QString::fromUtf8(ss.str().c_str()));*/

    /*frame->update(10000);

    stringstream ss;
    ss << "press : " << holder->isPressed();
    ui->label->setText(QString::fromUtf8(ss.str().c_str()));

    frame->endFrmae();*/
}

void Dialog::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        return;
    }
    keyPipe->keyPressEvent(event);
    /*stringstream ss;
    ss << "key down: " << event->key();
    ss << "   txt: " << event->text().toStdString() << endl;
    qDebug(ss.str().c_str());*/
 }

 void Dialog::keyReleaseEvent(QKeyEvent *event) {
     if (event->isAutoRepeat()) {
         return;
     }
     keyPipe->keyReleaseEvent(event);
     /*stringstream ss;
     ss << "key up: " << event->key();
     ss << "   txt: " << event->text().toStdString() << endl;
     qDebug(ss.str().c_str());*/
}
