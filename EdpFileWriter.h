//
// Created by admin on 2018/8/31.
//

#ifndef REPO1_EDPFILEWRITER_H
#define REPO1_EDPFILEWRITER_H


#include <fstream>
#include "types.h"
#include "EdpFile.h"


namespace edp{
    class EdpFileWriter {
    public:
        explicit EdpFileWriter(const string &path);
        explicit EdpFileWriter(EdpFile &file);
        ~EdpFileWriter();

        void close();

        void print(const string &str);
        void println(const string &str);
        void println();

        ostream &getRawStream();

        bool isError();
    private:
        ofstream out;
        bool err;
        bool closed;

        void initial(const string &path);
    };
}


#endif //REPO1_EDPFILEWRITER_H
