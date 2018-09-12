//
// Created by admin on 2018/9/4.
//

#ifndef QT_BB_BEATMAPDECODER_H
#define QT_BB_BEATMAPDECODER_H

#include "nsoclass.h"
#include "BaseDecoder.h"

namespace nso{
    class BeatmapDecoder: public BaseDecoder {
    public:
        explicit BeatmapDecoder(EdpFile &file);
        explicit BeatmapDecoder(const string &path);
    protected:
        virtual bool onBegin(Beatmap &beatmap);
        virtual void load();
    };

    class BackgroundParser:public PartParser {
    public:
        BackgroundParser();

        virtual void parseLine(const string &line, Beatmap &beatmap);

    private:
        bool hasParsed;
    };

    class TimingPointsParser:public PartParser {
    public:
        virtual void parseLine(const string &line, Beatmap &beatmap);
    };

    class HitObjectParser:public PartParser {
    public:
        virtual void parseLine(const string &line, Beatmap &beatmap);
    };
}


#endif //QT_BB_BEATMAPDECODER_H
