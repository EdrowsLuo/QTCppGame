#include "rightframe.h"
#include "ui_rightframe.h"

RightFrame::RightFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RightFrame)
{
    ui->setupUi(this);
}

RightFrame::~RightFrame()
{
    delete ui;
}
