//
// Created by admin on 2018/8/31.
//

#include "EdpFileWriter.h"

using namespace  edp;

EdpFileWriter::EdpFileWriter(const string &path) : err(false), closed(false) {
    initial(path);
}

EdpFileWriter::EdpFileWriter(EdpFile &file) : err(false), closed(false) {
    initial(file.getFullPath());
}

EdpFileWriter::~EdpFileWriter() {
    close();
}

void EdpFileWriter::initial(const string &path) {
    out.open(path.c_str());
    if (!out) {
        err = true;
    }
}

bool EdpFileWriter::isError() {
    return err;
}

void EdpFileWriter::close() {
    if (!err) {
        if (closed){
            out.flush();
            out.close();
            closed = true;
        }
    }
}

void EdpFileWriter::println(const string &str) {
    if (err) {
        throw ioexception("bad output stream");
    }
    out << str << endl;
}

void EdpFileWriter::print(const string &str) {
    if (err) {
        throw ioexception("bad output stream");
    }
    out << str;
}

void EdpFileWriter::println() {
    if (err) {
        throw ioexception("bad output stream");
    }
    out << endl;
}

ostream& EdpFileWriter::getRawStream() {
    return out;
}