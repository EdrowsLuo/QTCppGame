#ifndef DIFFICULTYSCROLLAREA_H
#define DIFFICULTYSCROLLAREA_H

#include <QScrollArea>
#include "myqsplitter.h"
#include "songs.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "Edp.h"
#include "EdpFile.h"
#include "IOUtil.h"
#include <string.h>
#include "cJSON.h"
#include "CJsonObject.hpp"
#include "my_song.h"

namespace Ui {
    class DifficultyScrollArea;
}

class DifficultyScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit DifficultyScrollArea(const My_Song & ,QWidget *parent = 0 );
    ~DifficultyScrollArea();
    MyQSplitter *my_splitter;
    int h;
   // QPropertyAnimation *appear,*disappear;
//    QGraphicsOpacityEffect  * myAnim;

private:
    Ui::DifficultyScrollArea *ui;
};

#endif // DIFFICULTYSCROLLAREA_H
