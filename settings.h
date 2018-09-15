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

signals:
    void CLOSED();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
