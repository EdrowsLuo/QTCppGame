#include "difficultyscrollarea.h"
#include "ui_difficultyscrollarea.h"
#include "QMessageBox"



DifficultyScrollArea::DifficultyScrollArea(const My_Song &jsong ,QWidget *parent ) :
    QScrollArea(parent),
    ui(new Ui::DifficultyScrollArea)
{
    ui->setupUi(this);
    h=jsong.difficultyset;
    this->setMinimumHeight(100);
    this->setMinimumWidth(0);
    my_splitter = new MyQSplitter( h, jsong ,this);
    this->setWidget(my_splitter);
 //   QMessageBox::about(NULL,"viewport", QString::number( this->viewport()->height() ));
 //   QMessageBox::about(NULL,"s", QString::number( this->viewport()->width()));
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setBackgroundRole(QPalette::Dark);
 //   this->setFrameShape(QFrame::NoFrame);

  //  myAnim = new QGraphicsOpacityEffect(this);
  //  myAnim->setOpacity(0.1);
   // this->setGraphicsEffect(myAnim);
   // this->repaint(0,0,500,600);

 /*   disappear=new QPropertyAnimation(this,"windowOpacity",this);
    disappear->setStartValue(1);
    disappear->setEndValue(0);
    disappear->setDuration(1000);
    disappear->start();
*/
}

DifficultyScrollArea::~DifficultyScrollArea()
{
//    QMessageBox::about(NULL,"ds","you" );
    //delete disappear;
    delete my_splitter;
    delete ui;
}
