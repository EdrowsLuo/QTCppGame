#include <QtGui/QApplication>
#include "mainwindow.h"
#include "Project.h"


int main(int argc, char *argv[])
{
    Game_Initial
    QApplication a(argc, argv);



    MainWindow w;
    w.show();

    return a.exec();
}
