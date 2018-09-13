#include "difficultyscrollarea.h"
#include "ui_difficultyscrollarea.h"
#include <QMessageBox>



DifficultyScrollArea::DifficultyScrollArea(const My_Song &jsong ,QWidget *parent ) :
    QScrollArea(parent),
    ui(new Ui::DifficultyScrollArea)
{
    ui->setupUi(this);
//    viewPort = new QWidget(this);

 //   this->setViewport(viewPort);
    h=jsong.difficultyset;
   // this->setMinimumHeight();
 //   this->setMinimumWidth(0);
    my_splitter = new MyQSplitter( h, jsong ,this);
    this->setWidget(my_splitter);
 //   QMessageBox::about(NULL,"viewport", QString::number( this->viewport()->height() ));
 //   QMessageBox::about(NULL,"s", QString::number( this->viewport()->width()));
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setBackgroundRole(QPalette::Dark);
    this->setFrameShape(QFrame::NoFrame);
    this->setWindowOpacity(0.1);
  //  myAnim = new QGraphicsOpacityEffect(this);
  //  myAnim->setOpacity(0.1);
   // this->setGraphicsEffect(myAnim);
   // this->repaint(0,0,500,600);
    this->setWidgetResizable(true);

//    this->setObjectName("doubi");
//    this->viewport()->setObjectName("doubi2");
    this->setStyleSheet("DifficultyScrollArea, QWidget#viewPort{background-color:transparent;}");

//    this->setStyleSheet("DifficultyScrollArea {background-color:transparent;}");
//    this->viewport()->setStyleSheet("QWidget{background-color:transparent;}");


//    this->setStyleSheet("DifficultyScrollArea {background-color:transparent;}");
//    this->viewport()->setStyleSheet("QPushButton[height=200]{background-color:transparent;}");

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
