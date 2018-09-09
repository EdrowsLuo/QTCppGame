//
// Created by admin on 2018/9/4.
//

#include "BeatmapDecoder.h"
#include "StringUtil.h"
#include <QDebug>

#define PS(n) putKey2String(#n, &Beatmap::n)
#define PI(n) putKey2Int(#n, &Beatmap::n)
#define PB(n) putKey2Bool(#n, &Beatmap::n)
#define PD(n) putKey2Double(#n, &Beatmap::n)


using namespace nso;

BeatmapDecoder::BeatmapDecoder(EdpFile &file) : BaseDecoder(file) { }
BeatmapDecoder::BeatmapDecoder(const string &path): BaseDecoder(path) { }

void BeatmapDecoder::load() {
    registerParser("General", (new BaseParser())
            ->PS(AudioFilename)
            ->PI(AudioLeadIn)
            ->PI(PreviewTime)
            ->PB(Countdown)
            ->PS(SampleSet)
            ->PD(StackLeniency)
            ->PI(Mode)
            ->PB(LetterboxInBreaks)
            ->PB(WidescreenStoryboard)
            ->PB(StoryFireInFront)
            ->PB(SpecialStyle)
            ->PB(EpilepsyWarning)
            ->PB(UseSkinSprites));

    registerParser("Metadata", (new BaseParser())
            ->PS(Title)
            ->PS(TitleUnicode)
            ->PS(Artist)
            ->PS(ArtistUnicode)
            ->PS(Creator)
            ->PS(Version)
            ->PS(Source)
            ->PS(Tags)
            ->PI(BeatmapID)
            ->PI(BeatmapSetID));

    registerParser("Difficulty", (new BaseParser())
            ->PD(HPDrainRate)
            ->PD(CircleSize)
            ->PD(OverallDifficulty)
            ->PD(ApproachRate)
            ->PD(SliderMultiplier)
            ->PD(SliderTickRate));

    registerParser("TimingPoints", new TimingPointsParser());
    registerParser("HitObjects", new HitObjectParser());
}

bool BeatmapDecoder::onBegin(Beatmap &beatmap) {
    //先找到format line
    while (toNextLine()) {
        StringUtil::trim(currentLine);
        if (currentLine.find("osu file format v") != string::npos) {
            string format = currentLine.substr(17, currentLine.size());
            StringUtil::trim(format);
            qDebug() << "get format : " << format.c_str();
            StringUtil::str2int(format, beatmap.format);
            return true;
        }
    }
    beatmap.latestErr = "format line not found!";
    return false;
}

#define unit(type,name) if(StringUtil::splitTo(nline, ',', part)){\
    StringUtil::str2##type(part, point.name);\
} else {\
    throw DecodeException("format err, name not found", beatmap.decoder);\
}

void TimingPointsParser::parseLine(const string &line, nso::Beatmap &beatmap) {
    string nline = line;
    StringUtil::trim(nline);
    if (nline.empty()) {
        return;
    }
    string part;
    RawTimingPoint point;
    unit(int,offset)
    unit(double,perbeat)
    unit(int,meter)
    unit(int,sampleSet)
    unit(int,sampleIndex)
    unit(int,volume)
    unit(int2bool,inherited)
    unit(int2bool,kiai)
    beatmap.timingPoints.timings.push_back(point);
    qDebug() << "parse timing at " << point.toString().c_str();
}

#define hunit(idx,prop) StringUtil::str2int(spl[idx], hitobj->prop)
void HitObjectParser::parseLine(const string &line, nso::Beatmap &beatmap) {
    string nline = line;
    StringUtil::trim(nline);
    if (nline.empty()) {
        return;
    }

    vector<string> spl;
    StringUtil::split(nline, ',', spl);

    if (spl.size() >= 5) {
        int type;
        StringUtil::str2int(spl[3], type);
        int objtype = type & HitObject::TYPE_MASK;
        switch (objtype) {
            case HitObject::TYPE_MANIA_HOLD:{
                if (spl.size() < 6) {
                    throw DecodeException("mania hold format err", beatmap.decoder);
                }
                ManiaHold *hitobj = new ManiaHold() ;
                hunit(0,x);
                hunit(1,y);
                hunit(2,time);
                hunit(3,type);
                hunit(4,hitSound);
                string endTime;
                StringUtil::splitTo(spl[5], ':', endTime);
                StringUtil::str2int(endTime, hitobj->endTime);
                beatmap.hitobjects.push_back(hitobj);
            }break;

            case HitObject::TYPE_CIRCLE:
            default:{
                //暂时不解析特殊情况
                HitCircle *hitobj = new HitCircle();
                hunit(0,x);
                hunit(1,y);
                hunit(2,time);
                hunit(3,type);
                hunit(4,hitSound);
                beatmap.hitobjects.push_back(hitobj);
            }
        }
    } else {
        throw DecodeException("hitobject format err", beatmap.decoder);
    }

}
