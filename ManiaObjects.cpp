//
// Created by admin on 2018/9/7.
//

#include "ManiaObjects.h"

#include "GameJudgement.h"

using namespace nso;
using namespace edp;

void nso::ManiaBaseJudgeObject::release() { //判定完了或超时进行释放
    if (!Released) {
        Released = true;
        onRelease();
    }
}

void nso::ManiaBaseJudgeObject::applyScore(nso::ManiaPlaytimeData *data, int type, int score, double offset) {
    ManiaHitResult result{type, score, offset};
    data->getScore()->applyScore(result);
    JudgeResult = score;
}

nso::ManiaNoteJudgeObject::ManiaNoteJudgeObject(nso::PlayingNote *note, nso::Beatmap *beatmap) : ManiaBaseJudgeObject(), Note(note) {
    RawBeatmap = beatmap;
    StartJudgeTime = note->getTime() - ManiaUtil::hitWindow(beatmap->OverallDifficulty, Mania::S_MISS);
    MaxJudgeTime = note->getTime();
    EndJudgeTime = note->getTime() + ManiaUtil::hitWindow(beatmap->OverallDifficulty, Mania::S50);
    Line = ManiaUtil::positionToLine(note, beatmap);
    Depth = note->getTime();
}

void nso::ManiaNoteJudgeObject::onJudge(nso::ManiaPlaytimeData *data) {
    KeyHolder *key = data->getKeys()[Line];
    if (key->parseMainState() == KeyState::Down) {
        int score = ManiaUtil::hitWindowFor(RawBeatmap->OverallDifficulty,
                                            Note->getTime() - key->getTime());
        applyScore(data, Mania::ScoreType_Note, score, Note->getTime() - key->getTime());
        key->consumeEvent();
        release();
    }
}

void nso::ManiaNoteJudgeObject::onRelease() {
    Note->release();
}

void nso::ManiaNoteJudgeObject::onTimeout(nso::ManiaPlaytimeData *data) {
    //note超时产生miss
    applyScore(data, Mania::ScoreType_Note, Mania::S_MISS, 100000);
}

nso::ManiaHoldStartJudgeObject::ManiaHoldStartJudgeObject(nso::PlayingHold *hold, nso::Beatmap *beatmap) : ManiaBaseJudgeObject(), Hold(hold) {
    RawBeatmap = beatmap;
    StartJudgeTime = hold->getTime() - ManiaUtil::hitWindow(beatmap->OverallDifficulty, Mania::S_MISS);
    MaxJudgeTime = hold->getTime();
    EndJudgeTime = hold->getTime() + ManiaUtil::hitWindow(beatmap->OverallDifficulty, Mania::S50);
    Line = ManiaUtil::positionToLine(hold, beatmap);
    Depth = hold->getTime();
}

void nso::ManiaHoldStartJudgeObject::onJudge(nso::ManiaPlaytimeData *data) {
    KeyHolder *key = data->getKeys()[Line];
    if (key->parseMainState() == KeyState::Down) {
        int score = ManiaUtil::hitWindowFor(RawBeatmap->OverallDifficulty,
                                            Hold->getTime() - key->getTime());
        applyScore(data, Mania::ScoreType_Note, score, Hold->getTime() - key->getTime());
        key->consumeEvent();
        release();
    }
}

void nso::ManiaHoldStartJudgeObject::onTimeout(nso::ManiaPlaytimeData *data) {
    //note超时产生miss
    applyScore(data, Mania::ScoreType_Note, Mania::S_MISS, 100000);
}

nso::ManiaHoldTickJudgeObject::ManiaHoldTickJudgeObject(nso::PlayingHold *hold, double offset, nso::Beatmap *beatmap) : ManiaBaseJudgeObject(), Hold(hold), pressed(false) {
    RawBeatmap = beatmap;
    StartJudgeTime = hold->getTime() - ManiaUtil::hitWindow(beatmap->OverallDifficulty, Mania::S300);
    MaxJudgeTime = hold->getTime() + offset;
    EndJudgeTime = hold->getTime() + offset + ManiaUtil::hitWindow(beatmap->OverallDifficulty, Mania::S300);
    Line = ManiaUtil::positionToLine(hold, beatmap);
    Depth = hold->getTime();
}

void nso::ManiaHoldTickJudgeObject::onJudge(nso::ManiaPlaytimeData *data) {
    if (pressed){
        //已经判定过了并且超过了标准时间
        if (data->getFrameTime() > MaxJudgeTime) {
            applyScore(data, Mania::ScoreType_Tick, Mania::S300k, 0);
            release();
            return;
        }
    } else {
        KeyHolder *key = data->getKeys()[Line];
        if (key->isPressed()) {
            pressed = true;
            if (data->getFrameTime() > MaxJudgeTime) {
                applyScore(data, Mania::ScoreType_Tick, Mania::S300k, 0);
                release();
                return;
            }
        }
    }
}

void nso::ManiaHoldTickJudgeObject::onTimeout(nso::ManiaPlaytimeData *data) {
    //note超时判断是否在时间段里摁下过
    applyScore(data, Mania::ScoreType_Tick, pressed ? Mania::S300k : Mania::S_MISS, 0);
}

nso::ManiaHoldEndJudgeObject::ManiaHoldEndJudgeObject(nso::PlayingHold *hold, nso::ManiaHoldStartJudgeObject *start,
                                                      vector<nso::ManiaHoldTickJudgeObject *> *ticks,
                                                      nso::Beatmap *beatmap)
        : ManiaBaseJudgeObject(), Hold(hold), StartObject(start), TickObjects(ticks), pressed(false) {
    RawBeatmap = beatmap;
    StartJudgeTime = hold->getEndTime() - ManiaUtil::hitWindow(beatmap->OverallDifficulty, Mania::S_MISS);
    MaxJudgeTime = hold->getEndTime();
    EndJudgeTime = hold->getEndTime() + ManiaUtil::hitWindow(beatmap->OverallDifficulty, Mania::S50);
    Line = ManiaUtil::positionToLine(hold, beatmap);
    Depth = hold->getEndTime();
}

void nso::ManiaHoldEndJudgeObject::onJudge(nso::ManiaPlaytimeData *data) {
    KeyHolder *key = data->getKeys()[Line];

    if (key->isPressed()) {
        pressed = true;
    }

    if (key->parseMainState() == KeyState::Up) {
        int score = ManiaUtil::hitWindowFor(RawBeatmap->OverallDifficulty,
                                            Hold->getTime() - key->getTime());
        key->consumeEvent();

        //查询是否在中间断过滑条
        bool hasBadTick = false;
        ForEachLong(*TickObjects,itr,vector<ManiaHoldTickJudgeObject*>::iterator) {
            ManiaHoldTickJudgeObject *tick = *itr;
            if (tick->getJudgeResult() <= Mania::S_MISS) {
                hasBadTick = true;
                break;
            }
        }

        applyScore(data, Mania::ScoreType_Note, Mania::S300k, 0);
        release();

        /*if (score > Mania::S_MISS) {
            if (StartObject->getJudgeResult() > Mania::S_MISS) {
                //滑条头摁下了
                if (hasBadTick) {
                    //中间有断滑条，最多判定为200
                    if (score > Mania::S200){
                        score = Mania::S200;
                    }
                }
                applyScore(data, Mania::ScoreType_Note, score, 0);
            } else {
                //滑条头没有摁到，最多判定200
                if (score > Mania::S200){
                    score = Mania::S200;
                }

                applyScore(data, Mania::ScoreType_Note, score, 0);
            }
            release();
        } else {
            //提前放开了滑条头，不做判定，跳到timeout
            return;
        }*/
    }
}

void nso::ManiaHoldEndJudgeObject::onTimeout(nso::ManiaPlaytimeData *data) {
    //滑条尾超时，没有接受到Up事件
    if (pressed) {
        //不做尾判

        applyScore(data, Mania::ScoreType_Note, Mania::S300k, 0);

        /*//没有松开滑条尾或者早松开了滑条尾，最多判定50

        //查询是否在中间断过滑条
        bool hasBadTick = false;
        ForEachLong(*TickObjects,itr,vector<ManiaHoldTickJudgeObject*>::iterator) {
            ManiaHoldTickJudgeObject *tick = *itr;
            if (tick->getJudgeResult() <= Mania::S_MISS) {
                hasBadTick = true;
                break;
            }
        }

        if (StartObject->getJudgeResult() <= Mania::S_MISS || hasBadTick) {
            //滑条头没判定或者中间断了，判定MISS
            applyScore(data, Mania::ScoreType_Note, Mania::S_MISS, 0);
        } else {
            applyScore(data, Mania::ScoreType_Note, Mania::S50, 0);
        }*/
    } else {
        //如果根本没有摁滑条尾
        applyScore(data, Mania::ScoreType_Note, Mania::S_MISS, 0);
    }
}

void nso::ManiaHoldEndJudgeObject::onRelease() {
    Hold->release();
}

ManiaHoldEndJudgeObject::~ManiaHoldEndJudgeObject() {
    delete TickObjects;
}


void nso::ManiaNoteObject::addPlayingObjects(vector<nso::JudgeableObject<nso::ManiaPlaytimeData> *> *judge,
                                             vector<nso::PlayingHitObject *> *draw) {

    PlayingNote *note = new PlayingNote(*RawObject);
    ManiaNoteJudgeObject *noteJudgeObject = new ManiaNoteJudgeObject(note, RawBeatmap);
    draw->push_back(note);
    judge->push_back(noteJudgeObject);
}

nso::ManiaNoteObject::ManiaNoteObject(nso::HitCircle *rawObject, nso::Beatmap *rawBeatmap) : RawObject(rawObject),
                                                                                             RawBeatmap(rawBeatmap) {

}

nso::ManiaHoldObject::ManiaHoldObject(nso::ManiaHold *rawObject, nso::Beatmap *rawBeatmap) : RawObject(rawObject),
                                                                                             RawBeatmap(rawBeatmap) {

}

void nso::ManiaHoldObject::addPlayingObjects(vector<nso::JudgeableObject<nso::ManiaPlaytimeData> *> *judge,
                                             vector<nso::PlayingHitObject *> *draw) {

    PlayingHold *hold = new PlayingHold(*RawObject);
    draw->push_back(hold);
    ManiaHoldStartJudgeObject *holdJudgeStartObject = new ManiaHoldStartJudgeObject(hold, RawBeatmap);
    judge->push_back(holdJudgeStartObject);
    vector<ManiaHoldTickJudgeObject*> *ticks = new vector<ManiaHoldTickJudgeObject*>;
    double beatlenth = RawBeatmap->controlPoints.getTimingControlPointAt(hold->getTime()).BeatLength;
    double offset = beatlenth;
    while (hold->getEndTime() > offset + hold->getTime()) {
        ManiaHoldTickJudgeObject *tick = new ManiaHoldTickJudgeObject(hold, offset, RawBeatmap);
        ticks->push_back(tick);
        judge->push_back(tick);
        offset += beatlenth;
    }
    ManiaHoldEndJudgeObject *endJudgeObject = new ManiaHoldEndJudgeObject(hold, holdJudgeStartObject, ticks,
                                                                          RawBeatmap);
    judge->push_back(endJudgeObject);
}
