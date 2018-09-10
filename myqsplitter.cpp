#include "myqsplitter.h"
#include <QMessageBox>
#include <QPushButton>


MyQSplitter::MyQSplitter( int nn,QWidget *parent , int heightOfScrollArea ) :
    QSplitter( parent )
{
    numberofwid = nn;
    for( int i = 0 ; i<numberofwid ; i++ ){
        f[i] = new QPushButton;
        f[i]->setMinimumHeight( heightOfScrollArea );

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
