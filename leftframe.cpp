#include "leftframe.h"
#include "defext.h"
#include "widget.h"



using namespace nso;
using namespace edp;




LeftFrame::LeftFrame(QWidget *parent) :
    QPushButton(parent)
{
}

LeftFrame::LeftFrame( const My_Difficulty & mydifficulty, string itplace , QWidget *parent ):
    QPushButton(parent)
{
        DebugI("fk")
    id = itplace;
    difficultyInfo = mydifficulty;
    connect(this,SIGNAL(clicked()),this,SLOT(onleftFrameClicked()));
    trans = new QGraphicsOpacityEffect(this);
    trans->setOpacity(0.6);
    this->setGraphicsEffect(trans);

}


void LeftFrame::onleftFrameClicked(){
    string root = "assets\\songs\\";
    root = root + id ;
    root = root + "\\";
    root = root +difficultyInfo.file;
    EdpFile f(*Project::ProjectRoot,root);
    string abroot = f.getFullPath();
    Project::ProjectGame->loadGame(&f);
    DebugI(abroot.c_str())
    emit passtosplitter();

}
