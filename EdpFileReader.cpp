//
// Created by admin on 2018/8/31.
//

#include "EdpFileReader.h"
#include "defext.h"
#include <iostream>
#include <typeinfo>

using namespace edp;

EdpFileReader::EdpFileReader(edp::EdpFile &file) : err(false), closed(false) {
    initial(file.getFullPath());
}

EdpFileReader::EdpFileReader(const string &path) : err(false), closed(false) {
    initial(path);
}

EdpFileReader::~EdpFileReader() {
    close();
}

void EdpFileReader::initial(const string &path) {
    in.open(path.c_str());
    if (!in) {
        //err = true;
    }
}

bool EdpFileReader::isError() {
    return err;
}

void EdpFileReader::close() {
    if (!err) {
        if (closed){
            in.close();
            closed = true;
        }
    }
}

bool EdpFileReader::readLine(string &ptr) {
    if (err)
        throw ioexception("bad input stream");
    try {
        if (getline(in, ptr)) {
            return true;
        } else {
            return false;
        }
    } catch (std::bad_cast& bc) {
        throw ioexception("bad_cast??");
    }
}

istream& EdpFileReader::getRawStream() {
    return in;
}