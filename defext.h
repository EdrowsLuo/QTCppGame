//
// Created by admin on 2018/9/5.
//

#ifndef QT_BB_DEFEXT_H
#define QT_BB_DEFEXT_H

#include <QDebug>
#include <sstream>
#include <string>

#define Debug(txt) qDebug(txt)

#define DebugI(txt) {\
stringstream ss;\
ss << txt;\
qDebug(ss.str().c_str());\
}

#define DebugS qDebug()

#define VGetter(type,name) virtual type get##name(){ return name; }

#define VaGetter(type,name) virtual type get##name()

#define InterfaceGetter(type,name) virtual type get##name() = 0;

#define OverrideGetter(type,name) virtual type get##name()

#define Getter(type,name) type get##name(){ return name; }

#define Setter(type,name) void set##name(const type &value){ name = value; }

#define GetSet(type,name) type get##name(){ return name; }\
void set##name(const type &value){ name = value; }

#define GetSetO(type,name) type *get##name(){ return name; }\
void set##name(type *value){ name = value; }

#define BoolGetSet(name) bool is##name(){ return name; }\
void set##name(const bool &value){ name = value; }

#define ForI(v,start,end) int xxv = (end);for(int v = (start); v < xxv; v++)

#define ForEach(obj,itr,func,...) {__VA_ARGS__ itr = obj.begin();\
for (; itr != obj.end(); itr++) {\
func;\
}}

#define ForEachLong(obj,itr,...) {__VA_ARGS__ itr = (obj).begin();\
for (; itr != (obj).end(); itr++)

#define RCase(data,func) case data:{\
 func;\
}break

#define DCase(data,func) case data:\
default:{\
 func;\
}break

#define Interface(txt) virtual txt = 0;

#define ToString virtual std::string toString();

/*template<typename _Type>
std::string strl(string r, _Type t){std::stringstream ss;ss << r << t;return ss.str();}*/

#define MapProp(name) #name << ": " << name

#define Clamp(min,value,max) (((min) < (value))?(((max) < (value))? (max):(value)):(min))

#endif //QT_BB_DEFEXT_H
