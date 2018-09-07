//
// Created by admin on 2018/9/4.
//

#ifndef QT_BB_STRINGUTIL_H
#define QT_BB_STRINGUTIL_H

#include <string>
#include <sstream>

using namespace std;

class StringUtil {
public:
    static void trim(string &str){
        if (str.empty()) {
            return;
        }
        str.erase(0,str.find_first_not_of(' '));
        str.erase(str.find_last_not_of(' ') + 1);
    }

    static void raw(const string &str,string &target){
        target = str;
    }

    static void str2int(const string &str,int &target) {
        stringstream ss;
        ss << str;
        ss >> target;
    }

    static void str2long(const string &str,long &target) {
        stringstream ss;
        ss << str;
        ss >> target;
    }

    static void str2double(const string &str, double &target) {
        stringstream ss;
        ss << str;
        ss >> target;
    }

    static void str2int2bool(const string &str,bool &target) {
        if (str == "true") {
            target = true;
            return;
        }
        if (str == "false") {
            target = false;
            return;
        }
        stringstream ss;
        ss << str;
        int i;
        ss >> i;
        target = (i != 0);
    }

    static void split(string &raw, char c, vector<string> &out) {
        string copy = raw;
        string part;
        while (splitTo(copy, c, part)) {
            out.push_back(part);
        }
    }

    static bool splitTo(string &raw, char c, string &ret) {
        unsigned int where = raw.find(c);
        if (where == string::npos) {
            string s=raw;
            trim(raw);
            if (s.empty()) {
                return false;
            } else {
                ret = s;
                raw = "";
                return true;
            }
        } else {
            ret = raw.substr(0, where);
            if (where >= raw.size() - 1) {
                raw = "";
                return true;
            } else {
                raw = raw.substr(where + 1, raw.size() - 1);
            }
            trim(ret);
            trim(raw);
            return true;
        }
    }
};


#endif //QT_BB_STRINGUTIL_H
