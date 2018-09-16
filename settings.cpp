#include "settings.h"
#include "ui_settings.h"
#include "Project.h"

using namespace nso;

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->spinBox,SLOT(setValue(int)));
    connect(ui->spinBox,SIGNAL(valueChanged(int)),ui->horizontalSlider,SLOT(setValue(int)));
    ui->spinBox->setValue(40);
    ui->verticalSlider->setValue(40);
    this->setAutoFillBackground(true);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    this->close();
}


void Settings::on_verticalSlider_valueChanged(int value)
{
    Project::ProjectGame->setSpeedLevel(value/4);
}

void Settings::on_horizontalSlider_valueChanged(int value)
{
    Project::ProjectGame->setBaseVolume((double)value/100.0);
}
