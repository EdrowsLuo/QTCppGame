//
// Created by admin on 2018/8/31.
//

#ifndef REPO1_IOUTIL_H
#define REPO1_IOUTIL_H


#include "EdpFile.h"

using namespace edp;

class IOUtil {
public:
    static void readFull(EdpFile &file, string &ptr);

    static void writeFull(EdpFile &file, const string &data);
};


#endif //REPO1_IOUTIL_H
