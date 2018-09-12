#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEffect>
#include "slidebox1.h"
#include <QHBoxLayout>
#include "difficultyscrollarea.h"
#include "songgroup.h"
#include <QMessageBox>
#include <QAction>
#include "Edp.h"
#include "EdpFile.h"
#include "IOUtil.h"
#include "cstring"
#include "cJSON.h"
#include "CJsonObject.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SlideBox1 * RightBox;
    DifficultyScrollArea *LeftBox[2];
    void UpDateSize();
    QString *ss;
//    string *SongName;
    SongGroup s;

    int SN,ST;

//    int numOfSong;

    int modeNumber;

    QPropertyAnimation *leftBoxAppear,*leftBoxDisappear;
    QPropertyAnimation *startButtonDisappear,*setButtonDisappear,*exitButtonDisappear,*titleDisappear;
    QPropertyAnimation *startButtonAppear,*setButtonAppear,*exitButtonAppear,*titleAppear;

    QPropertyAnimation *leftBoxAppear0,*rightBoxAppear0;
    QPropertyAnimation *leftBoxDisappear0,*rightBoxDisappear0;
    QPropertyAnimation *upButtonAppear , *upButtonDisappear;
    QPropertyAnimation *modeButtonAppear , *modeButtonDisappear;
//    QPushButton *l;
    bool al,a2;
    Songs *Songinfo[7];
    QGraphicsOpacityEffect *uppaged;


 //   QString *CreaterName;

public slots:
    void SN_ADD();
    void SN_SUB();//
    void SN_SUB_ANIM1();

signals:
    void CHANGE_TO_AUTO();
    void CHANGE_TO_MANUAL();

private slots:
    void on_StartButton_clicked();
    void onChooseSurfaceAppear();
    void onStartSurfaceAppear();

    void on_upButton_clicked();

    void on_ExitButton_clicked();

    void on_ModeButton1_clicked();

private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent *);
    int lx,ly,lw,lh;
    int rx,ry,rw,rh;
    int ux,uy,uw,uh;
    int sx,sy,sw,sh,sd;
    int lbx,lby,lbw,lbh;
    int mx,my,mw,mh;


//    QPushButton * upButton;

    void SongACopyB( Songs * a , Songs * b );
};

#endif // MAINWINDOW_H
