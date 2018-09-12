//
// Created by admin on 2018/8/31.
//

#include <sstream>
#include <iostream>
#include "IOUtil.h"
#include "EdpFileReader.h"
#include "EdpFileWriter.h"

void IOUtil::readFull(EdpFile &file, string &ptr) {
    stringstream strbuilder;
    EdpFileReader reader(file);
    string line;
    while (reader.readLine(line)) {
        strbuilder << line << endl;
    }
    ptr =  strbuilder.str();
}

void IOUtil::writeFull(EdpFile &file, const string &data) {
    EdpFileWriter writer(file);
    writer.print(data);
    writer.close();
}
