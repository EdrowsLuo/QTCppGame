//
// Created by admin on 2018/9/5.
//

#ifndef QT_BB_DEFEXT_H
#define QT_BB_DEFEXT_H

#include <QDebug>
#include <sstream>

#define Debug(txt) qDebug(txt)

#define DebugI(txt) {\
stringstream ss;\
ss << txt;\
qDebug(ss.str().c_str());\
}

#define DebugS qDebug()

#define Getter(type,name) type get##name(){ return name; }

#define Setter(type,name) void set##name(const type &value){ name = value; }

#define GetSet(type,name) type get##name(){ return name; }\
void set##name(const type &value){ name = value; }

#define GetSetO(type,name) type *get##name(){ return name; }\
void set##name(type *value){ name = value; }

#define BoolGetSet(name) bool is##name(){ return name; }\
void set##name(const bool &value){ name = value; }

#define Nulp(data,func) if(data){func;}

#define ForEach(obj,itr,func,...) {__VA_ARGS__ itr = obj.begin();\
for (; itr != obj.end(); itr++) {\
func;\
}}

#define ForEachLong(obj,itr,...) {__VA_ARGS__ itr = obj.begin();\
for (; itr != obj.end(); itr++)

#define RCase(data,func) case data:{\
 func;\
}break

#define DCase(data,func) case data:\
default:{\
 func;\
}break

#define Interface(txt) virtual txt = 0;

#endif //QT_BB_DEFEXT_H
