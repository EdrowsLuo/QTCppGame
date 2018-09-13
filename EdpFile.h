//
// Created by admin on 2018/8/30.
//

#ifndef REPO1_FILE_H
#define REPO1_FILE_H

#include <string>
#include <io.h>
#include <vector>
#include "types.h"
#include "defext.h"

using namespace std;

namespace edp{

    const char PATH_SEPARATOR = '\\';

    class Type{
    public:
        static const int File=1, Dir=2, None=0;
    };

    class ioexception : public exception {
    public:
        string mmsg;

        explicit ioexception(const string& msg){
            mmsg = msg;
            DebugI(msg)
        }

        ~ioexception() throw(){

        }

        const char *what(){
            return mmsg.c_str();
        }
    };

    class EdpFile {
    public:
        explicit EdpFile(const string& path);
        EdpFile(EdpFile &dir, string name);
        EdpFile(const EdpFile &obj);

        int getFileType();
        void list(vector<string> &files);
        void listFiles(vector<EdpFile> &files);

        string getFullPath();
        string getName();

        string getParentPath();

        bool isFile();
        bool isDirectory();
        bool exist();

        bool createNewFile();
        bool createNewFileWithDir();
        bool mkdirs();

        bool deleteFile();

        //static string getAbusolutPathFromRoot(string &rpath);
    private:
        void initial();
        static string getParentPath(string &path);
    protected:
        int mtype;
        string mpath;
    };
}


#endif //REPO1_FILE_H
