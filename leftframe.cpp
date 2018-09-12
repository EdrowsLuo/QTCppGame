#include "leftframe.h"

LeftFrame::LeftFrame(QWidget *parent) :
    QPushButton(parent)
{
}

LeftFrame::LeftFrame( const My_Difficulty & mydifficulty, int n , QWidget *parent ){
    id = n;
    difficultyInfo = mydifficulty;
    connect(this,SIGNAL(clicked()),this,SLOT(onleftFrameClicked()));

}


void LeftFrame::onleftFrameClicked(){

}
