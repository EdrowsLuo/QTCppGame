//
// Created by admin on 2018/9/13.
//

#include "MyGLBaseView.h"

using namespace mywidget;

int MW::CUSTOM_INDEX = 0;

int floatToRawIntBits(float size) {
    int *tmp = (int *) &size;
    return *tmp;
}

float intBitsToFloat(int size) {
    float *tmp = (float *)&size;
    return *tmp;
}
