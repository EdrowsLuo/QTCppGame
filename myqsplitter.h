#ifndef MYQSPLITTER_H
#define MYQSPLITTER_H

#include <QSplitter>
#include <QPushButton>
#include "songs.h"

class MyQSplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit MyQSplitter( int nn , QWidget *parent = 0 , int heightOfScrollArea = 0 );
    ~MyQSplitter();

    int numberofwid;
    QPushButton *f[10];

    int splitterHeight;

signals:

public slots:

};

#endif // MYQSPLITTER_H
