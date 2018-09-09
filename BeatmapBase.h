//
// Created by admin on 2018/9/8.
//

#ifndef QT_BB_BEATMAPBASE_H
#define QT_BB_BEATMAPBASE_H

#include <string>
#include <vector>

using namespace std;

namespace nso{

    class BeatmapBase;

    class BeatmapSetBase;

    class BeatmapSetBase {
        vector<BeatmapBase*> Beatmaps;
    };

    class BeatmapBase {
        string Path; // .osu文件路径

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

        double Star;

        //Events events;
        string backgroundFile;
    };
}



#endif //QT_BB_BEATMAPBASE_H
