#ifndef RIGHTFRAME_H
#define RIGHTFRAME_H

#include <QFrame>

namespace Ui {
    class RightFrame;
}

class RightFrame : public QFrame
{
    Q_OBJECT

public:
    explicit RightFrame(QWidget *parent = 0);
    ~RightFrame();

private:
    Ui::RightFrame *ui;
};

#endif // RIGHTFRAME_H
