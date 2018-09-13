#ifndef MYQSPLITTER_H
#define MYQSPLITTER_H

#include <QSplitter>
#include <QPushButton>
#include"Edp.h"
#include "EdpFile.h"
#include "IOUtil.h"
#include <string.h>
#include "cJSON.h"
#include "CJsonObject.hpp"
#include "my_song.h"
#include "leftframe.h"
#include <QGraphicsOpacityEffect>
#include <QLayout>

class MyQSplitter : public QWidget
{
    Q_OBJECT
public:
    explicit MyQSplitter( int nn , const My_Song & , QWidget *parent = 0 );
    ~MyQSplitter();

    int numberofwid;
    LeftFrame *f[12];

    QHBoxLayout *layout;
    QGraphicsOpacityEffect *op;

    int splitterHeight;

signals:

public slots:

};

#endif // MYQSPLITTER_H
