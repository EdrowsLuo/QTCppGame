//
// Created by admin on 2018/9/4.
//

#ifndef QT_BB_FILEDECODER_H
#define QT_BB_FILEDECODER_H

#include <io.h>
#include <string>
#include "EdpFileReader.h"
#include "Beatmap.h"
#include "iostream"
#include "nsoclass.h"
#include <map>
#include <QDebug>
#include "defext.h"
#include <sstream>

using namespace std;
using namespace edp;

namespace nso{

    class DecodeException;
    class PartParser;
    class BaseDecoder;
    class DataParser;
    template <typename _Data> class DataInjecter;
    class BaseParser;


    class DecodeException:exception{
    public:
        explicit DecodeException(const string &msg,BaseDecoder *decoder);
        ~DecodeException() throw();
        const char *what();
    private:
        string m;
        string where;
        int line;
        string content;
        string rmsg;
    };

    class PartParser{
    public:
        //开始解析时的操作
        virtual void onParseStart(Beatmap &beatmap, BaseDecoder &decoder){};
        //解析一行数据，并存入beatmap
        Interface(void parseLine(const string &line, Beatmap &beatmap))
        //当结束解析时被调用
        virtual void onParseEnd(Beatmap &beatmap, BaseDecoder &decoder){};
    };

    class BaseDecoder {

    public:
        //存储解析时的一些设定数据
        map<string,string> parseProperty;

        string currentLine;
        int parsingLine;

        explicit BaseDecoder(const string &data);
        explicit BaseDecoder(EdpFile &file);
        virtual ~BaseDecoder();

        static bool parseTag(string &line, string &tag);

        //解析并将数据放入beatmap
        void parse(Beatmap &beatmap);

        void registerParser(const string &key, PartParser *parser);

        void close();
    protected:
        map<string,PartParser*> parserMap;
        //EdpFileReader reader;

        stringstream input;

        bool toNextLine();
        virtual bool onBegin(Beatmap &beatmap){ return true; };
        virtual void load(){};
    };

    class DataParser{
    public:
        virtual void parseData(const string &line, Beatmap &beatmap) = 0;
    };

    template <typename _Data>
    class DataInjecter: public DataParser{
    public:
        DataInjecter(_Data Beatmap::* t, void (*c)(const string &,_Data &data))
                :target(t),converter(c){ }

        virtual void parseData(const string &line, Beatmap &beatmap){
            converter(line,beatmap.*target);
            //DebugI(beatmap.*target)
        }
    protected:
        _Data Beatmap::* target;
        void (*converter)(const string &,_Data &data);
    };

    class BaseParser: public PartParser {
    public:
        map<string,DataParser*> parsers;

        BaseParser *putParser(const string &key, DataParser *parser);
        BaseParser *putKey2Bool(const string &key, bool Beatmap::* target);
        BaseParser *putKey2Int(const string &key, int Beatmap::* target);
        BaseParser *putKey2Long(const string &key, long Beatmap::* target);
        BaseParser *putKey2String(const string &key, string  Beatmap::* target);
        BaseParser *putKey2Double(const string &key, double Beatmap::* target);

        virtual void parseLine(const string &line, Beatmap &beatmap);

        virtual void passBaseParse(const string &line, Beatmap &beatmap){}
    };
}



#endif //QT_BB_FILEDECODER_H
