#include "coordinate.h"
#include <cmath>
coordinate::coordinate(int a)
{
    judge=a;
}

void coordinate::calculateSize1(int trackenum,double Pos){
    if (judge==1){
        x1=320*trackenum+((480+80*trackenum)-320*trackenum)*Pos;
        x2=320*(trackenum+1)+((480+80*(trackenum+1))-320*(trackenum+1))*Pos;
        y1=612-528*Pos;
        y2=612-528*Pos;
    }
    if (judge==0){
        x1=1280/7*trackenum+((480+320/7*trackenum)-1280/7*trackenum)*Pos;
        x2=1280/7*trackenum+((480+320/7*trackenum)-1280/7*trackenum)*Pos;
        y1=612-528*Pos;
        y2=612-528*Pos;
    }
}

double coordinate::setoutx1(){
    return x1;
}

double coordinate::setoutx2(){
    return x2;
}

double coordinate::setouty1(){
    return y1;
}

double coordinate::setouty2(){
    return y2;
}

