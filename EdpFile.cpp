//
// Created by admin on 2018/8/30.
//

#include <stdexcept>
#include <iostream>
#include <vector>
#include <fstream>
#include <direct.h>
#include <stack>
#include <string.h>
#include "EdpFile.h"

using namespace edp;

EdpFile::EdpFile(EdpFile &dir,string name){ // NOLINT
    if (dir.getFileType() != Type::Dir) {
        throw invalid_argument("err param : a directory is needed");
    } else {
        mpath = dir.getFullPath() + PATH_SEPARATOR + name;
        initial();
    }
}

EdpFile::EdpFile(const string& path) { // NOLINT
    mpath = path;
    initial();
}

EdpFile::EdpFile(const edp::EdpFile &obj) {
    mpath = obj.mpath;
    mtype = obj.mtype;
}

void EdpFile::initial() {
    //规定mpath不能以分割符结尾
    while (*(mpath.end() - 1) == PATH_SEPARATOR) {
        mpath = mpath.substr(0, mpath.size() - 1);
    }

    if (_access(mpath.c_str(), 00) != -1) {
        //文件存在
        _finddata_t fileinfo; // NOLINT
        long handle = _findfirst(mpath.c_str(), &fileinfo);
        if (handle != -1) {
            if ((fileinfo.attrib & _A_SUBDIR)) {
                mtype = Type::Dir;
            } else {
                mtype = Type::File;
            }
        } else {
            //获取失败？？
            throw ioexception("get file attrib failed!");
        }
    } else {
        //文件不存在
        mtype = Type::None;
    }
}

int EdpFile::getFileType() {
    return mtype;
}

string EdpFile::getFullPath() {
    return mpath;
}

void EdpFile::listFiles(vector<edp::EdpFile> &files) {
    if (mtype != Type::Dir) {
        throw ioexception("you can only call listFiles() with a dir!");
    }

    _finddata_t fileinfo;// NOLINT
    long handle = _findfirst((mpath + "\\*").c_str(), &fileinfo);
    if (handle != -1) {
        do {
            //TODO: 解决内存溢出
            if (strcmp(fileinfo.name, "..") != 0 && strcmp(fileinfo.name, ".") != 0)
                files.push_back(*new EdpFile(*this, fileinfo.name));
        } while (_findnext(handle, &fileinfo) == 0);
    } else {
        //获取失败？？
        throw ioexception("get file attrib failed!");
    }
}

void EdpFile::list(vector<string> &files) {
    if (mtype != Type::Dir) {
        throw ioexception("you can only call list() with a dir!");
    }

    _finddata_t fileinfo; // NOLINT
    long handle = _findfirst((mpath + "\\*").c_str(), &fileinfo);
    if (handle != -1) {
        do {
            if (strcmp(fileinfo.name, "..") != 0 && strcmp(fileinfo.name, ".") != 0)
                files.push_back(fileinfo.name); // NOLINT
        } while (_findnext(handle, &fileinfo) == 0);
    } else {
        //获取失败？？
        throw ioexception("get file attrib failed!");
    }
}

string EdpFile::getName() {
    return mpath.substr(mpath.find_last_of(PATH_SEPARATOR)+1);
}

string EdpFile::getParentPath() {
    return getParentPath(mpath);
}

string EdpFile::getParentPath(string &path) {
    return path.substr(0, path.find_last_of(PATH_SEPARATOR));
}

bool EdpFile::isDirectory() {
    return mtype == Type::Dir;
}

bool EdpFile::isFile() {
    return mtype == Type::File;
}

bool EdpFile::exist() {
    return mtype != Type::None;
}

bool EdpFile::createNewFile() {
    if (exist()) {
        return false;
    } else {
        fstream fs;
        fs.open(mpath.c_str(), ios::out);
        if (!fs) {
            return false;
        } else {
            fs.close();
            return true;
        }
    }
}

bool EdpFile::createNewFileWithDir() {
    EdpFile parent(getParentPath());
    parent.mkdirs();
    return createNewFile();
}

bool EdpFile::mkdirs() {
    if (mtype == Type::None) {
        stack<string> dirstack;
        dirstack.push(mpath);
        string path = getParentPath(mpath);
        while (_access(path.c_str(), 00) == -1) {
            dirstack.push(path);
        }
        while (!dirstack.empty()) {
            if (_mkdir(dirstack.top().c_str()) != 0) {
                return false;
            }
            dirstack.pop();
        }
        return true;
    } else {
        return false;
    }
}

bool EdpFile::deleteFile() {
    return -1 != remove(mpath.c_str());
}