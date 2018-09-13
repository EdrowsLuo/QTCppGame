//
// Created by admin on 2018/9/13.
//

#ifndef QT_BB_JMATH_H
#define QT_BB_JMATH_H

#include "javastyle.h"

namespace javastyle {
    class jmath {
        public template<typename T> static T min(T x, T y) {
            return x < y ? x : y;
        }

    public template<typename T> static T max(T x,T y) {
            return x < y ? y : x;
        }
    };
}



#endif //QT_BB_JMATH_H
