#include "addcas.h"

AddCAS::AddCAS(double a,double b,double c,double d,int e)
{
    address1 = Project::fromRoot("assets\\image\\Combo.png").c_str();
    address2 = Project::fromRoot("assets\\image\\Accuracy.png").c_str();
    address3 = Project::fromRoot("assets\\image\\Score.png").c_str();

}

void AddCAS::draw(QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    painter->restore();
}


