#include "myqsplitter.h"
#include <QMessageBox>
#include <QPushButton>
#include <string>
#include <QApplication>




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
        f[i]->setStyleSheet("QPushButton{background-color:transparent;border-image:url(:/C:/Users/HJ/Pictures/QT/Infographic-with-crystal-banners/081-01.png)}"
                           "QPushButton::hover{background-color:transparent;border-image:url(:/C:/Users/HJ/Pictures/QT/Infographic-with-crystal-banners/031.png)}"
                            "QPushButton::pressed{background-color:transparent;border-image:url(:/C:/Users/HJ/Pictures/QT/Infographic-with-crystal-banners/032.png)}" );
   //     f[i]->setStyleSheet("border-image:url(:/C:/Users/HJ/Pictures/QT/fakeButton4.png);"
   //                        "background-color:transparent;");
        string content = jsong.difficultylist[i].version;

        //content = content + "\n";
        //content = content + jsong.difficultylist[i].version.c_str();
        //content = content + "\n";
        const char*  ch;
        ch=content.c_str();
  //      DebugI(ch)
  //              DebugI("fk")
        f[i]->setText(QApplication::translate("", ch, 0, QApplication::UnicodeUTF8));
 //       content = content + (char)jsong.difficultylist[i].overalldifficulty

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
