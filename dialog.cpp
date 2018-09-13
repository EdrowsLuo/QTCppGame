#include "dialog.h"
#include "ui_dialog.h"
#include "TestView.h"
#include <QKeyEvent>
#include <QTimer>
#include <QtGui>

#include <string>
#include <sstream>
#include "Project.h"

using namespace std;
using namespace nso;

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
    layout->addWidget(ui->pushButton_5, 4, 0);
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
    if (Project::ProjectGame->getGame()->running()){
        Project::ProjectGame->getGame()->pauseGame();
    } else {
        Project::ProjectGame->getGame()->runGame();
    }
    Debug("clicked");
    //view->Game->pauseGame();
    //view->Game->runGame();
}

void Dialog::on_pushButton_2_clicked()
{
    Project::ProjectGame->reloadGame();
    Project::ProjectGame->startGame();
}

void Dialog::animate() {

}

void Dialog::on_horizontalSlider_valueChanged(int value)
{
    Project::ProjectGame->getGame()->getSongChannel()->setVolume(value / 100.0f);
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
void Dialog::on_pushButton_5_clicked()
{
    EdpFile *osuFile = new EdpFile(
            //"D:\\My\\osu!droid\\Songs\\375548 Hashimoto Yukari - Hakanaki Yume\\Hashimoto Yukari - Hakanaki Yume (Bearizm) [Timing].osu"
            //"D:\\Qt\\code\\qt_bb\\data\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [4K Lv.4].osu"
            //"D:\\Qt\\code\\qt_bb\\data\\356253 ginkiha - Borealis\\ginkiha - Borealis ([ A v a l o n ]) [CS' ADVANCED].osu"
            "D:\\Qt\\code\\qt_bb\\data\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [Starry's 4K Lv.15].osu"
    );
    Project::ProjectGame->loadGame(osuFile);
}
