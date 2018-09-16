//
// Created by admin on 2018/9/8.
//

#ifndef QT_BB_UTIL_HH
#define QT_BB_UTIL_HH

#include <sys/timeb.h>
#include <sys/types.h>
#include <sstream>
#include "defext.h"

using namespace std;

class util{
public:
    static long long currentTimeMS(){
        struct timeb t;
        ftime(&t);
        return  ((long long) t.time) * 1000 + t.millitm;
    }

    static int clamp(int min, int data, int max) {
        return (data < min ? min : (data < max ? data : max));
    }

    static string formatTimeMS(int ms) {
        ms /= 1000;
        int min = ms / 60;
        int s = ms % 60;
        if (s < 10) {
            MakeString(txt,min << ":0" << s)
            return txt;
        } else {
            MakeString(txt,min << ":" << s)
            return txt;
        }
    }
};

#endif //QT_BB_UTIL_H
