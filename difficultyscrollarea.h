#ifndef DIFFICULTYSCROLLAREA_H
#define DIFFICULTYSCROLLAREA_H

#include <QScrollArea>
#include "myqsplitter.h"
#include "songs.h"
#include "QPropertyAnimation"
#include <QGraphicsOpacityEffect>

namespace Ui {
    class DifficultyScrollArea;
}

class DifficultyScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit DifficultyScrollArea(const Songs & s,QWidget *parent = 0 );
    ~DifficultyScrollArea();
    MyQSplitter *my_splitter;
    int h;
   // QPropertyAnimation *appear,*disappear;
    QGraphicsOpacityEffect  * myAnim;

private:
    Ui::DifficultyScrollArea *ui;
};

#endif // DIFFICULTYSCROLLAREA_H
