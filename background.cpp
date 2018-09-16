#include "background.h"
#include "Project.h"

using namespace nso;

BackGround::BackGround() : pixmap(NULL)
{
    //address = new QString;
    address = Project::fromRoot("assets\\image\\a021f3383448084929d0878cb1d4fc50.jpg").c_str();
    pixmap = new QPixmap;
    pixmap->load(address);
}
void BackGround::draw (QPaintEvent *event, QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    if (Project::ProjectGame->isEnableBackground()) {
        painter->drawPixmap(0,0,1280,720,*pixmap);
    } else {
        QPainterPath pathbb1;
        pathbb1.moveTo(0,0);
        pathbb1.lineTo(1280,0);
        pathbb1.lineTo(1280,720);
        pathbb1.lineTo(0,720);
        painter->setBrush(QColor(40, 44, 53));
        painter->drawPath(pathbb1);
    }


    //QPixmap Pixmap0;
    //Pixmap0.load(address);

    /*QPainterPath pathq;
    pathq.moveTo(0,0);
    pathq.lineTo(0,720);
    pathq.lineTo(1280,720);
    pathq.lineTo(1280,0);
    pathq.lineTo(0,0);
    painter->setBrush(QColor(100,100,100));
    painter->drawPath(pathq);*/
    QPainterPath pathblack;
    pathblack.moveTo(0,0);
    pathblack.lineTo(0,720);
    pathblack.lineTo(1280,720);
    pathblack.lineTo(1280,0);
    painter->setBrush(QColor(0,0,0,50));
    painter->drawPath(pathblack);
    QLinearGradient linearGradient(640,612,640,84);
    linearGradient.setColorAt(0,QColor(0,162,219,255));
    linearGradient.setColorAt(1,QColor(0,162,219,90));
    QLinearGradient linearGradient2(640,612,640,84);
    linearGradient2.setColorAt(0,QColor(0,162,219,255));
    linearGradient2.setColorAt(1,QColor(0,162,219,90));
    QPainterPath path;
    path.moveTo(0,528);
    path.lineTo(480,60);
    path.lineTo(480,84);
    path.lineTo(0,612);
    path.lineTo(0,528);
    painter->setPen(QColor(170,225,255));
    painter->setBrush(linearGradient2);
    painter->drawPath(path);;


    QPainterPath path2;
    path2.moveTo(1280,528);
    path2.lineTo(800,60);
    path2.lineTo(800,84);
    path2.lineTo(1280,612);
    path2.lineTo(1280,528);
    /*QLinearGradient linearGradient2(800,470,500,60);
    linearGradient2.setColorAt(0,QColor(0,0,0));
    linearGradient2.setColorAt(0.2,QColor(255,255,255));
    linearGradient2.setColorAt(0.4,QColor(0,0,0));
    linearGradient2.setColorAt(0.6,QColor(255,255,255));
    linearGradient2.setColorAt(0.8,QColor(0,0,0));
    linearGradient2.setColorAt(1,QColor(255,255,255));*/
    painter->setPen(QColor(170,225,255));
    painter->setBrush(linearGradient2);
    painter->drawPath(path2);;


    QPainterPath path3;
    path3.moveTo(0,288);
    path3.lineTo(496,0);
    path3.lineTo(512,0);
    path3.lineTo(0,408);
    path3.lineTo(0,288);
    /*QLinearGradient linearGradient3(0,290,315,0);
    linearGradient3.setColorAt(0,QColor(0,0,0));
    linearGradient3.setColorAt(0.2,QColor(255,255,255));
    linearGradient3.setColorAt(0.4,QColor(0,0,0));
    linearGradient3.setColorAt(0.6,QColor(255,255,255));
    linearGradient3.setColorAt(0.8,QColor(0,0,0));
    linearGradient3.setColorAt(1,QColor(255,255,255));*/
    painter->setPen(QColor(170,225,255));
    painter->setBrush(linearGradient);
    painter->drawPath(path3);

    QPainterPath path4;
    path4.moveTo(1280,288);
    path4.lineTo(784,0);
    path4.lineTo(768,0);
    path4.lineTo(1280,408);
    path4.lineTo(1280,288);
    /*QLinearGradient linearGradient4(800,290,485,0);
    linearGradient4.setColorAt(0,QColor(0,0,0));
    linearGradient4.setColorAt(0.2,QColor(255,255,255));
    linearGradient4.setColorAt(0.4,QColor(0,0,0));
    linearGradient4.setColorAt(0.6,QColor(255,255,255));
    linearGradient4.setColorAt(0.8,QColor(0,0,0));
    linearGradient4.setColorAt(1,QColor(255,255,255));*/
    painter->setPen(QColor(170,225,255));
    painter->setBrush(linearGradient);
    painter->drawPath(path4);

    QPainterPath path5;
    path5.moveTo(0,612);
    path5.lineTo(1280,612);
    path5.lineTo(1280,720);
    path5.lineTo(0,720);
    /*path5.moveTo(0,684);
    path5.lineTo(1280,684);
    path5.lineTo(1280,720);
    path5.lineTo(0,720);*/
    painter->setPen(QColor(3,20,40));
    painter->setBrush(QColor(3,20,40,235));
    painter->drawPath(path5);
    //painter->setPen(Qt::white);
    //painter->drawLine(800,540,0,540);
    /*QPainterPath path6;
    path6.moveTo(0,660);
    path6.lineTo(1280,660);
    path6.lineTo(1280,684);
    path6.lineTo(0,684);
    painter->setPen(QColor(130,0,0));
    painter->setBrush(QColor(130,0,0));
    painter->drawPath(path6);*/
   /* painter->setPen(Qt::white);
    painter->drawLine(1280,660,0,660);*/

    painter->restore();
}
