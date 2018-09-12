#ifndef DIFFICULTYFRAME_H
#define DIFFICULTYFRAME_H

#include <QFrame>

namespace Ui {
    class DifficultyFrame;
}

class DifficultyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit DifficultyFrame(QWidget *parent = 0);
    ~DifficultyFrame();

private:
    Ui::DifficultyFrame *ui;
};

#endif // DIFFICULTYFRAME_H
