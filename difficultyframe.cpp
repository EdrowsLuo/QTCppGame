#include "difficultyframe.h"
#include "ui_difficultyframe.h"

DifficultyFrame::DifficultyFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DifficultyFrame)
{
    ui->setupUi(this);
}

DifficultyFrame::~DifficultyFrame()
{
    delete ui;
}
