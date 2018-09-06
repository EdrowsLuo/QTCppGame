#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "EdpBass.h"
#include "KeyIO.h"

using namespace edp;

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::Dialog *ui;

    EdpBassChannel *channel;

    KeyFrame *frame;
    KeyHolder *holder;
    QTKeyPipe *keyPipe;

private slots:
    void on_pushButton_4_clicked();
    void on_progressBar_valueChanged(int value);
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void animate();
};

#endif // DIALOG_H
