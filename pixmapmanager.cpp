#include "pixmapmanager.h"
#include <QPixmap>
#include <QString>
Pixmapmanager::Pixmapmanager()
{
}

QPixmap *Pixmapmanager::get(const string &path){
    if(datas.find(path) != datas.end()){
        return datas[path];
    }else{
        QPixmap *tmp = new QPixmap();
        QString sss(path.c_str());
        tmp->load(sss);
        datas[path] = tmp;
        return tmp;
    }
}
