//
// Created by admin on 2018/9/8.
//

#ifndef QT_BB_UTIL_HH
#define QT_BB_UTIL_HH

#include <sys/timeb.h>
#include <sys/types.h>

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
};

#endif //QT_BB_UTIL_H
