#ifndef PIXMAPMANAGER_H
#define PIXMAPMANAGER_H

#include <map>
#include <string>
#include <QPixmap>

using namespace std;

class Pixmapmanager
{
public:
    Pixmapmanager();

    QPixmap *get(const string &path);

private:
    map<string,QPixmap*> datas;
};

#endif // PIXMAPMANAGER_H
