#ifndef LEFTFRAME_H
#define LEFTFRAME_H

#include <QPushButton>
#include "Project.h"
#include "my_difficulty.h"

class LeftFrame : public QPushButton
{
    Q_OBJECT
public:
    explicit LeftFrame(QWidget *parent = 0);
    explicit LeftFrame( const My_Difficulty &, int , QWidget *parent = 0 );
    My_Difficulty difficultyInfo;
    int id;

signals:

public slots:
    void onleftFrameClicked();

};
/*class LeftFrameSlot : public QObject
{
    Q_OBJECT
public:
    LeftFrameSlot( int LID );
    LeftFrameSlot();
    int ID;

signals:
    void finishChoose();

public slots:
    void onDifficultyButtonClicked();
};
*/

#endif // LEFTFRAME_H
