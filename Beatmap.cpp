//
// Created by admin on 2018/9/4.
//

#include "Beatmap.h"

nso::TimingControlPoint &nso::ControlPoints::getTimingControlPointAt(double time) {
    return binarySearch(Timings, (int) (time + 0.001));
}

template<typename _T>
_T &nso::ControlPoints::binarySearch(vector<_T> &l, int value, int s, int e) {
    if (e - s <= 1) {
        return l[s];
    } else {
        int m = (s + e) / 2;
        _T tmp = l[m];
        if (tmp.Time <= value) {
            return binarySearch(l, value, m, e);
        } else {
            return binarySearch(l, value, s, m);
        }
    }
}

template<typename _T>
_T &nso::ControlPoints::binarySearch(vector<_T> &l, int value) {
    if (value < l[0].Time) {
        return l[0];
    } else if (value >= l[l.size() - 1].Time) {
        return l[l.size() - 1];
    } else {
        return binarySearch(l, value, 0, l.size());
    }
}

void nso::ControlPoints::load(nso::TimingPoints &datas) {
    if (datas.timings.size() < 1) {
        return;
    } else {
        RawTimingPoint &raw = datas.timings[0];
        TimingControlPoint preTp;
        preTp.Time = raw.offset;
        preTp.BeatLength = raw.perbeat;
        preTp.Meter = raw.meter;

        Timings.push_back(preTp);

        int size = datas.timings.size();

        ForI(i, 1, size) {
            raw = datas.timings[i];
            if (raw.inherited) {
                preTp.Time = raw.offset;
                preTp.BeatLength = raw.perbeat;
                preTp.Meter = raw.meter;

                Timings.push_back(preTp);
            }
        }

        sort(Timings.begin(), Timings.end(), tmpfunc::sortcp<TimingControlPoint>);
    }
}

void nso::ControlPoints::generateBeats(vector<double> &l, double start, double end) {
    TimingControlPoint &tp = Timings[0];
    double beat = start;
    if (tp.Time > beat) {
        double ext = tp.Time;
        while (ext - beat > tp.BeatLength * tp.Meter) {
            ext -= tp.BeatLength * tp.Meter;
        }
        beat = ext;
    } else {
        double ext = tp.Time;
        while (beat - ext > tp.BeatLength * tp.Meter) {
            ext += tp.BeatLength * tp.Meter;
        }
        beat = ext;
    }
    TimingControlPoint &next = Timings.size() > 1 ? Timings[1] : Timings[0];
    //补全中间区间
    ForI(i, 1, Timings.size()) {
        tp = Timings[i - 1];
        next = Timings[i];
        while (beat < next.Time) {
            l.push_back(beat);
            beat += tp.BeatLength * tp.Meter;
        }
        beat = next.Time;
    }
    //添加末尾
    while (beat < end) {
        l.push_back(beat);
        beat += tp.BeatLength * tp.Meter;
    }
}

void nso::ControlPoints::generateBeats(double start, double end) {
    generateBeats(Beats, start, end);
}
