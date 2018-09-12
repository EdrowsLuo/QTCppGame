#include "mainwindow.h"

using namespace nso;

void MainWindow::SN_ADD(){
    if(al==0){
        leftBoxDisappear->stop();
        LeftBox[((SN+100)+1)%2]->deleteLater();
//            LeftBox[(SN+1)%2]=NULL;
        LeftBox[(SN+100)%2]->show();
        LeftBox[(SN+100)%2]->setGeometry(QRect(lx,ly,lw,lh));
    }
 //   DebugL("");
    al=0;
    //a2=1;
    leftBoxDisappear->setTargetObject(LeftBox[(SN+100)%2]);
//    DebugL("x");
    leftBoxDisappear->setStartValue(QRect(lx,ly,lw,lh));
    leftBoxDisappear->setEndValue(QRect(0-lw,ly,lw,lh));
    leftBoxDisappear->setDuration(400);
    leftBoxDisappear->setEasingCurve(QEasingCurve::InBack);
    leftBoxDisappear->start(QAbstractAnimation::KeepWhenStopped);
    SN++;
    ST++;
    if (ST>=s.Number) ST = 0;
    if (ST<0) ST = s.Number-1;
 //   DebugL("y")
    LeftBox[(SN+100)%2] = new DifficultyScrollArea(s.songlist[(ST+s.Number)%s.Number],this);
    DebugL("y1")
    string place = "assets\\songs\\" + s.songlist[(ST+s.Number)%s.Number].fileName;
    EdpFile f(*Project::ProjectRoot,place);
    string fullpath = f.getFullPath();
 //   Project::ProjectGame->loadMusic(fullpath);
}


void MainWindow::SN_SUB(){
    if(al==0){
        leftBoxDisappear->stop();
        LeftBox[((SN+100)+1)%2]->deleteLater();
//            LeftBox[(SN+1)%2]=NULL;
        LeftBox[(SN+100)%2]->show();
        LeftBox[(SN+100)%2]->setGeometry(QRect(lx,ly,lw,lh));
  //      LeftBox[(SN+1)%2] = new DifficultyScrollArea
 //       a2 = 0;
    }
//        DebugL("")
    al=0;
    leftBoxDisappear->setTargetObject(LeftBox[(SN+100)%2]);
    leftBoxDisappear->setStartValue(QRect(lx,ly,lw,lh));
    leftBoxDisappear->setEndValue(QRect(0-lw,ly,lw,lh));
    leftBoxDisappear->setDuration(400);
    leftBoxDisappear->setEasingCurve(QEasingCurve::InBack);
    leftBoxDisappear->start(QAbstractAnimation::KeepWhenStopped);
    SN--;
    ST--;
    if (ST>=s.Number) ST = 0;
    if (ST<0) ST = s.Number-1;
    LeftBox[(SN+100)%2] = new DifficultyScrollArea(s.songlist[(ST+s.Number)%s.Number],this);

}

void MainWindow::SN_SUB_ANIM1(){
//        DebugL("z")
    al = 1;
 //   if ( a2 == 1 )

 //   LeftBox[(SN+1)%2]=NULL;
//    DebugL("l")
 //   a2 = 1;
    LeftBox[(SN+100)%2]->show();
    LeftBox[(SN+100)%2]->setGeometry(0-lw,ly,lw,lh);
    leftBoxAppear->setTargetObject(LeftBox[(SN+100)%2]);

    leftBoxAppear->setDuration(400);
    leftBoxAppear->setStartValue(QRect(0-lw,ly,lw,lh));
    leftBoxAppear->setEndValue(QRect(lx,ly,lw,lh));
    leftBoxAppear->setEasingCurve(QEasingCurve::OutBack);
    leftBoxAppear->start();
//        DebugL("l")
 //   LeftBox[(SN+1)%2]->deleteLater();
 //           DebugL("d")
}
