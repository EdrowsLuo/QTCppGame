//
// Created by admin on 2018/9/4.
//

#include "BaseDecoder.h"
#include "StringUtil.h"
#include "string"
#include "defext.h"

using namespace nso;
using namespace edp;

BaseDecoder::BaseDecoder(EdpFile &file) : parserMap(), parseProperty(), reader(file) {

}

BaseDecoder::BaseDecoder(const string &path) : parserMap(), parseProperty(), reader(path) {

}

BaseDecoder::~BaseDecoder() {
    delete &reader;
    delete &parserMap;
    delete &parseProperty;
}

void BaseDecoder::registerParser(const string &key, nso::PartParser *parser) {
    parserMap[key] = parser;
}

bool BaseDecoder::toNextLine() {
    if (reader.readLine(currentLine)){
        //qDebug() << currentLine.c_str() << currentLine.size();
        parsingLine++;
        return true;
    } else {
        return false;
    }
}

bool BaseDecoder::parseTag(string &line, string &tag) {
    if (line.size() >= 2 && line.at(0) == '[' && line.at(line.size() - 1) == ']') {
        tag = line.substr(1, line.size() - 2);
        return true;
    } else {
        return false;
    }
}

void BaseDecoder::parse(Beatmap &beatmap) {
    beatmap.decoder = this;
    load();
    if (onBegin(beatmap)) {
        string tag;
        PartParser *parser = NULL;
        while (toNextLine()) {
            if (parseTag(currentLine, tag)) {
                //切换tag
                if (parser) {
                    parser->onParseEnd(beatmap, *this);
                    parser = NULL;
                }
                map<string,PartParser*>::iterator itr = parserMap.find(tag);
                if (itr != parserMap.end()) {
                    parser = itr->second;
                    parser->onParseStart(beatmap, *this);
                } else {
                    parser = NULL;
                }
            } else {
                if (parser) {
                    parser->parseLine(currentLine, beatmap);
                }
            }
        }
        if (parser) {
            parser->onParseEnd(beatmap, *this);
            parser = NULL;
        }
    } else {
        throw DecodeException(beatmap.latestErr, this);
    }
}


void BaseParser::parseLine(const string &line, Beatmap &beatmap) {
    string nline = line;//创建副本
    StringUtil::trim(nline);
    if (nline.empty()) {
        passBaseParse(line, beatmap);
        return;
    }
    int spl = nline.find(':');
    if (spl != string::npos) {
        string key = nline.substr(0, spl);
        //qDebug() << "key : " << key.c_str();
        DataParser *parser = parsers[key];
        if (parser) {
            string data = nline.substr(spl + 1, nline.size());
            StringUtil::trim(data);
            parser->parseData(nline, beatmap);
            qDebug() << "write to \"" << key.c_str() << "\" : " << data.c_str();
        } else {
            passBaseParse(line, beatmap);
            return;
        }
    } else {
        passBaseParse(line, beatmap);
        return;
    }
}

BaseParser* BaseParser::putParser(const string &key, DataParser *parser) {
    parsers[key] = parser;
    return this;
}

BaseParser* BaseParser::putKey2Bool(const string &key, bool Beatmap::* target) {
    parsers[key] = new DataInjecter<bool>(target, StringUtil::str2int2bool);
    return this;
}

BaseParser* BaseParser::putKey2Int(const string &key, int Beatmap::* target) {
    parsers[key] = new DataInjecter<int>(target, StringUtil::str2int);
    return this;
}

BaseParser* BaseParser::putKey2Long(const string &key, long Beatmap::* target) {
    parsers[key] = new DataInjecter<long>(target, StringUtil::str2long);
    return this;
}

BaseParser* BaseParser::putKey2Double(const string &key, double Beatmap::* target) {
    parsers[key] = new DataInjecter<double>(target, StringUtil::str2double);
    return this;
}

BaseParser* BaseParser::putKey2String(const string &key, string Beatmap::* target) {
    parsers[key] = new DataInjecter<string>(target, StringUtil::raw);
    return this;
}



DecodeException::DecodeException(const string &msg,BaseDecoder *decoder) {
    rmsg = msg;
    content = decoder->currentLine;
    line = decoder->parsingLine;
}

DecodeException::~DecodeException() throw(){

}

const char* DecodeException::what() {
    //qDebug() << rmsg.c_str() << endl;
    //qDebug() << "(" << line << ") " << content.c_str();
    return rmsg.c_str();
}