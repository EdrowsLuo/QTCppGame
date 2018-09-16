#include "myqsplitter.h"
#include <QMessageBox>
#include <QPushButton>
#include <string>
#include <QApplication>
#include "defext.h"
#include "Util.h"


MyQSplitter::MyQSplitter( int nn, const My_Song & jsong, QWidget *parent ) :
    QSplitter( parent )
{
    numberofwid = nn;
    for( int i = 0 ; i<numberofwid ; i++ ){
        string songplace = jsong.fileName;
        f[i] = new LeftFrame(jsong.difficultylist[i],songplace,this);
        f[i]->setMinimumHeight( 200 );
        f[i]->setObjectName("sb");
        connect(f[i],SIGNAL(passtosplitter()),this,SLOT(passedtosplitter()));
        string t = util::formatTimeMS(jsong.difficultylist[i].lenth);

        MakeString(s,"Version: " << jsong.difficultylist[i].version <<"  Star: " << jsong.difficultylist[i].star << endl<<"OverallDifficulty: "<< jsong.difficultylist[i].overalldifficulty << endl << "  KeyCount: " <<jsong.difficultylist[i].circlesize <<"  Length: "<<t);
        const char*  ch;
        ch=s.c_str();


        f[i]->setStyleSheet("QPushButton{background-color:transparent;border-image:url(:/assets/image/textbox-01.png);color:white}"
                           "QPushButton::hover{background-color:transparent;border-image:url(:/assets/image/textbox2-01.png);color:white}" );
        f[i]->setText(QApplication::translate("", ch, 0, QApplication::UnicodeUTF8));
        this->addWidget(f[i]);
    }
    this->setOrientation(Qt::Vertical);
    this->setHandleWidth(5);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setChildrenCollapsible(false);
//    QMessageBox::about(NULL,"ds","fuck" );
    this->setParent(parent);
    this->setStyleSheet("MyQSplitter{background-color:transparent}MyQSplitter::handle{background-color:transparent}");
  //  this->setWindowOpacity(0.3);
//    op = new QGraphicsOpacityEffect(this);
//    op->setOpacity(0.5);
//    this->setGraphicsEffect(op);
}

MyQSplitter::~MyQSplitter(){
    for( int i = 0 ; i<numberofwid ; i++ ){
        delete f[i];
    }
}

void MyQSplitter::passedtosplitter(){
    DebugI("doubi")
    emit StartGame();
}
