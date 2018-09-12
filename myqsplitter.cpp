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
        f[i] = new QPushButton;
        f[i]->setMinimumHeight( 200 );
        f[i]->setObjectName("sb");

        string content = jsong.difficultylist[i].version;

        //content = content + "\n";
        //content = content + jsong.difficultylist[i].version.c_str();
        //content = content + "\n";
        const char*  ch;
        ch=content.c_str();
        DebugI(ch)
                DebugI("fk")
        f[i]->setText(QApplication::translate("", ch, 0, QApplication::UnicodeUTF8));
 //       content = content + (char)jsong.difficultylist[i].overalldifficulty

        this->addWidget(f[i]);
    }
    this->setOrientation(Qt::Vertical);
    this->setHandleWidth(20);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setChildrenCollapsible(false);
//    QMessageBox::about(NULL,"ds","fuck" );
}

MyQSplitter::~MyQSplitter(){
    for( int i = 0 ; i<numberofwid ; i++ ){
        delete f[i];
    }
}
