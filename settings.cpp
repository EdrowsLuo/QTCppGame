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
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    this->close();
}

void Settings::on_pushButton_3_clicked()
{
    emit CLOSED();
}

void Settings::on_verticalSlider_valueChanged(int value)
{

}
