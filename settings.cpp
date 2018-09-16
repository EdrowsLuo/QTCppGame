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
    connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),ui->spinBox_2,SLOT(setValue(int)));
    connect(ui->spinBox_2,SIGNAL(valueChanged(int)),ui->horizontalSlider_2,SLOT(setValue(int)));
    ui->spinBox->setValue(40);
    ui->spinBox_2->setValue(40);
    this->setStyleSheet("QWidget#Settings{background-color:RGB(40,44,53)}");

}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    this->close();
}



void Settings::on_horizontalSlider_valueChanged(int value)
{
    Project::ProjectGame->setBaseVolume((double)value/100.0);
}

void Settings::on_horizontalSlider_2_valueChanged(int value)
{
    Project::ProjectGame->setSpeedLevel(value/4);
}
