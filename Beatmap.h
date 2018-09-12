//
// Created by admin on 2018/9/4.
//

#ifndef QT_BB_BEATMAP_H
#define QT_BB_BEATMAP_H

#include <string>
#include <vector>
#include <sstream>
#include "BaseDecoder.h"
#include "nsoclass.h"
#include "defext.h"
#include "algorithm"

using namespace std;

namespace nso{

    class General{
    public:
        string AudioFilename;
        int AudioLeadIn;
        int PreviewTime;
        bool Countdown;
        string SampleSet;
        double StackLeniency;
        int Mode;
        bool LetterboxInBreaks;
        bool WidescreenStoryboard;
        bool StoryFireInFront;
        bool SpecialStyle;
        bool EpilepsyWarning;
        bool UseSkinSprites;
    };

    class Editor{
    public:
        vector<int> Bookmarks;
        double DistanceSpacing;
        int BeatDivisor;
        int GridSize;
        int TimelineZoom;

        ~Editor(){
            delete &Bookmarks;
        }
    };

    class Metadata{
    public:
        string Title;
        string TitleUnicode;
        string Artist;
        string ArtistUnicode;
        string Creator;
        string Version;
        string Source;
        string Tags;
        int BeatmapID;
        int BeatmapSetID;
    };

    class Difficulty{
    public:
        double HPDrainRate;
        double CircleSize;
        double OverallDifficulty;
        double ApproachRate;
        double SliderMultiplier;
        double SliderTickRate;
    };

    class Events{
    public:
        string backgroundFile;
    };

    struct RawTimingPoint{
        int offset;
        double perbeat;
        int meter;
        int sampleSet;
        int sampleIndex;
        int volume;
        bool inherited;
        bool kiai;

        string toString(){
            stringstream ss;
            ss << offset << ','
               << perbeat << ','
               << meter << ','
               << sampleSet << ','
               << sampleIndex << ','
               << volume << ','
               << inherited << ','
               << kiai;
            return ss.str();
        }
    };


    struct TimingControlPoint{
    public:
        int Time;
        int Meter;
        double BeatLength;

    };

    class TimingPoints{
    public:
        vector<RawTimingPoint> timings;
    };

    namespace tmpfunc{
        template <typename _T>
        bool sortcp(_T t1,_T t2){
            return t1.Time < t2.Time;
        }
    }

    class ControlPoints{
    public:
        void load(TimingPoints &datas);

        TimingControlPoint &getTimingControlPointAt(double time);

        void generateBeats(double start, double end);

        void generateBeats(vector<double> &l, double start, double end);


        vector<TimingControlPoint> Timings;

        vector<double > Beats;

    private:
        template<typename _T>
        static _T &binarySearch(vector<_T> &l, int value, int s, int e);

        template<typename _T>
        static _T &binarySearch(vector<_T> &l, int value);


    };

    class Colours{

    };

    //只解析mania相关
    class HitObject{
    public:
        static const int TYPE_CIRCLE = 1, TYPE_SLIDER = 2, TYPE_SPINNER = 8, TYPE_MANIA_HOLD = 128;
        static const int TYPE_MASK = TYPE_CIRCLE + TYPE_SLIDER + TYPE_SPINNER + TYPE_MANIA_HOLD;
        static const int NEW_COMBO_MASK = 4;
        static const int COLOURS_TO_SKIP_MASK = 16 + 32 + 64;
        int x;
        int y;
        int time;
        int type;
        int hitSound;
        //ToString
    };

    class HitCircle:public HitObject{
        /*virtual string toString(){
            stringstream ss;
            ss << "<circle> " << MapProp(type) << ", "
                    << MapProp(time);
            return ss.str();
        }*/
    };

    class ManiaHold:public HitObject {
    public:
        int endTime;
        /*virtual string toString(){
            stringstream ss;
            ss << "<hold> " << MapProp(type) << ", "
               << MapProp(time) << ", "
               << MapProp(endTime);
            return ss.str();
        }*/
    };


    class Beatmap {
    public:
        BaseDecoder *decoder;

        int format;
        string latestErr;

        //General general;
        string AudioFilename;
        int AudioLeadIn;
        int PreviewTime;
        bool Countdown;
        string SampleSet;
        double StackLeniency;
        int Mode;
        bool LetterboxInBreaks;
        bool WidescreenStoryboard;
        bool StoryFireInFront;
        bool SpecialStyle;
        bool EpilepsyWarning;
        bool UseSkinSprites;

        //Editor editor;
        vector<int> Bookmarks;
        double DistanceSpacing;
        int BeatDivisor;
        int GridSize;
        int TimelineZoom;

        //Metadata metadata;
        string Title;
        string TitleUnicode;
        string Artist;
        string ArtistUnicode;
        string Creator;
        string Version;
        string Source;
        string Tags;
        int BeatmapID;
        int BeatmapSetID;

        //Difficulty difficulty;
        double HPDrainRate;
        double CircleSize;
        double OverallDifficulty;
        double ApproachRate;
        double SliderMultiplier;
        double SliderTickRate;

        //Events events;
        string BackgroundFile;

        ControlPoints controlPoints;

        TimingPoints timingPoints;
        Colours colours;

        vector<HitObject*> hitobjects;

        ~Beatmap() {
            ForEachLong(hitobjects, itre, vector<HitObject *>::iterator) {
                HitObject *object = *itre;
                delete object;
            }
        }

        void loadMore() {
            controlPoints.load(timingPoints);
        }

        int getKeys(){
            return static_cast<int>(CircleSize + 0.0001);
        }
    };
}



#endif //QT_BB_BEATMAP_H
