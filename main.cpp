#include <QtGui/QApplication>
#include "mainwindow.h"
#include "Project.h"


int main(int argc, char *argv[])
{
    Game_Initial
    QApplication a(argc, argv);

    QString * ss = new QString[2];
    ss[0] = "aaa";
    ss[1] = "xxx";
    SlideBox1 s(2, ss);
    s.show();

    MainWindow w;
    w.show();

    return a.exec();
}
