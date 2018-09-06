//
// Created by admin on 2018/8/31.
//

#ifndef REPO1_EDPFILEREADER_H
#define REPO1_EDPFILEREADER_H

#include <fstream>
#include "types.h"
#include "EdpFile.h"


namespace edp{
    class EdpFileReader {
    public:
        explicit EdpFileReader(const string &path);
        explicit EdpFileReader(EdpFile &file);
        ~EdpFileReader();

        void close();
        bool readLine(string &ptr);

        istream &getRawStream();

        bool isError();
    private:
        ifstream in;
        bool err;
        bool closed;

        void initial(const string &path);
    };
}




#endif //REPO1_EDPFILEREADER_H
