#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

namespace Ui {
    class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    int d;
signals:
    void CLOSED();

private slots:
    void on_pushButton_clicked();


    void on_horizontalSlider_valueChanged(int value);



    void on_horizontalSlider_2_valueChanged(int value);




    void on_pushButton_2_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
