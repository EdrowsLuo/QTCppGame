//
// Created by admin on 2018/9/6.
//

#include <QtGui>
#include "TestView.h"
#include "defext.h"
#include "Util.h"
#include "BeatmapDecoder.h"

#include "ManiaRuleset.h"

using namespace nso;


class MKeyHolder:public KeyHolder{
public:
    //消耗掉事件停止继续的操作
    virtual void consumeEvent(){

    }

    void acceptDownEvent(){
        if (!KeyState::isPressed(State)) {
            State |= KeyState::Down;
            State |= KeyState::Pressed;
            Debug("down");
        }
        //Debug("down");
    }

    void clear(){
        KeyState::clearState(State, KeyState::Down | KeyState::Up);
        if (cancel) {
            cancel = false;
            State = 0;
        }
    }

    virtual void pass() {

    }
};

MKeyHolder *oHolder;
int oOffset;

TestView::TestView(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {
    setFixedSize(1200,900);

    setAutoFillBackground(false);

    EdpFile *osuFile = new EdpFile(
            //"D:\\My\\osu!droid\\Songs\\375548 Hashimoto Yukari - Hakanaki Yume\\Hashimoto Yukari - Hakanaki Yume (Bearizm) [Timing].osu"
            //"D:\\Qt\\code\\qt_bb\\data\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [4K Lv.4].osu"
            "D:\\Qt\\code\\qt_bb\\data\\356253 ginkiha - Borealis\\ginkiha - Borealis ([ A v a l o n ]) [CS' ADVANCED].osu"
            //"D:\\Qt\\code\\qt_bb\\data\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [Starry's 4K Lv.15].osu"
            );
    Game = new ManiaGame(osuFile,new ManiaSetting());

    Game->prepareGame();
    keyPipe = new QTKeyPipe();
    keyPipe->setTimer(Game->getSongChannel());

    autoPlay = new AutoKeyPipe();
    autoPlay->load(Game->getOsuBeatmap(), Game->getSetting());

    Game->linkKeyInput(
            autoPlay
            //keyPipe
            );

    oHolder = new MKeyHolder();
    Game->getPlayingData()->getMKeyFrame()->registerHolder(Qt::Key_Z, oHolder);

    Debug("created");
}

void TestView::animate() {
    /*playtimeData->update();
    drawdata->update(playtimeData->getFrameTime());*/
    repaint();
    /*playtimeData->endJudge();*/
}

void TestView::paintEvent(QPaintEvent *event) {
    if (Game->updateTime()) {
        autoPlay->update(Game->getFrameTime());
        Game->update();
    }


    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(event->rect(), QBrush(QColor(83, 158, 215)));

    int wheight = 800;

    QPen pen(QColor(40,44,53));
    int offset = 100;
    int width = 80;

    painter.save();
    painter.setPen(pen);
    painter.setBrush(QColor(40,44,53));
    painter.drawRect(QRect(offset, 0, width * 4, wheight));
    painter.restore();


    painter.save();
    pen.setColor(QColor(255,255,255));
    painter.setPen(pen);
    for (int i = 0; i < 5; ++i) {
        painter.drawLine(offset + width * i, 0, offset + width * i, wheight);
    }
    painter.drawLine(offset + width * 5, 0, offset + width * 5, static_cast<int>(Game->getPlayingData()->getFrameTime() / 100));
    painter.restore();

    painter.save();
    pen.setColor(QColor(255,255,255));
    QLinearGradient linearGradient(0, 250, 0, 550);
    linearGradient.setColorAt(0, QColor(0, 0, 0, 0));
    linearGradient.setColorAt(1, QColor(255, 255, 255, 100));
    linearGradient.setSpread(QGradient::PadSpread);

    painter.setPen(pen);


    //painter.setBrush(QBrush(Qt::FDiagPattern));
    vector<ManiaDrawdataNode> &datas = Game->getDrawdata()->getDatas();

    //DebugI(datas.size())
    //DebugI(playtimeData->getFrameTime())

    int judgePosition = 550;
    int fieldHeight = 700;
    int noteHeight = 10;
    int holdPadding = 15;


    QLinearGradient linearGradient2(0, 0, 0, 200);
    linearGradient2.setColorAt(0, QColor(83, 158, 215, 0));
    linearGradient2.setColorAt(1, QColor(83, 158, 215, 255));
    linearGradient2.setSpread(QGradient::PadSpread);

    painter.setBrush(linearGradient2);

    linearGradient2.setColorAt(0, QColor(83, 158, 215, 0));
    linearGradient2.setColorAt(1, QColor(83, 158, 215, 255));
    painter.setBrush(linearGradient2);
    ForEachLong(*Game->getDrawdata()->getBeatsAvalibe(),itr,vector<double>::iterator) {
        int p = static_cast<int>(fieldHeight * (1 - *itr));
        painter.drawLine(offset,p,offset+width*4,p);
    }

    ForEachLong(datas,it,vector<ManiaDrawdataNode>::iterator) {
        if (it->line == 1 || it->line == 2) {
            linearGradient2.setColorAt(0, QColor(150, 200, 255, 0));
            linearGradient2.setColorAt(1, QColor(150, 200, 255, 255));
            painter.setBrush(linearGradient2);
        } else {
            linearGradient2.setColorAt(0, QColor(83, 158, 215, 0));
            linearGradient2.setColorAt(1, QColor(83, 158, 215, 255));
            painter.setBrush(linearGradient2);
        }
        if (it->type == HitObject::TYPE_MANIA_HOLD) {

            painter.drawRect(QRectF(
                    offset + width * it->line + holdPadding,
                    fieldHeight * (1 - it->endposition) + noteHeight,
                    width - holdPadding * 2,
                    fieldHeight * (it->endposition - it->position) - noteHeight * 2
            ));

            /*painter.drawLine(offset + width * it->line + 20,
                             (int) (fieldHeight * (1 - it->position)),
                             offset + width * it->line + 20,
                             (int) (fieldHeight * (1 - it->position)) + 50);*/

            painter.drawRect(QRectF(
                    offset + width * it->line,
                    fieldHeight * (1 - it->endposition) - noteHeight,
                    width,
                    noteHeight * 2
            ));
            painter.drawRect(QRectF(
                    offset + width * it->line,
                    fieldHeight * (1 - it->position) - noteHeight,
                    width,
                    noteHeight * 2
            ));
        } else {
            painter.drawRect(QRectF(
                    offset + width * it->line,
                    fieldHeight * (1 - it->position) - noteHeight,
                    width,
                    noteHeight * 2
            ));
        }
    }

    linearGradient2.setColorAt(0, QColor(83, 158, 215, 0));
    linearGradient2.setColorAt(1, QColor(83, 158, 215, 255));

    pen.setColor(QColor(255,255,255));
    painter.setPen(pen);
    painter.drawRect(QRectF(
            offset + width * 1,
            fieldHeight - noteHeight,
            width,
            noteHeight * 2
    ));
    painter.drawRect(QRectF(
            offset + width * 2,
            fieldHeight - noteHeight,
            width,
            noteHeight * 2
    ));


    pen.setColor(QColor(240,240,240));
    painter.setPen(pen);
    painter.drawRect(QRectF(
            offset + width * 0,
            fieldHeight - noteHeight,
            width,
            noteHeight * 2
    ));

    pen.setColor(QColor(240, 0, 0));
    painter.setPen(pen);

    if (oHolder->parseMainState() == KeyState::Down) {
        int time = (int) oHolder->getTime();
        time -= 690;
        time %= 400;
        if (time > 200) {
            time = time - 400;
        }
        oOffset = time;
        DebugI(oOffset)
    }

    oHolder->clear();

    painter.drawRect(QRectF(
            offset,
            fieldHeight * (1 - oOffset / 800.0) - noteHeight,
            width,
            noteHeight * 2
    ));


    pen.setColor(QColor(240,240,240));
    painter.setPen(pen);
    painter.setBrush(linearGradient);
    for (int i = 0; i < 4; ++i) {
        if (Game->getPlayingData()->getKeys()[i]->isPressed()) {
            painter.drawRect(QRect(offset + i * width, 0, width, wheight));
        }
    }

    stringstream ss;
    ss << Game->getPlayingData()->getScore()->RecentScore << " - " ;
    ss << Game->getPlayingData()->getScore()->TotalHit << " - " ;
    ss << Game->getPlayingData()->getScore()->getScore();
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(50);
    painter.setFont(font);
    painter.drawText(200,55,ss.str().c_str());

    painter.restore();


    painter.end();
}



void TestView::mkeyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        return;
    }

    keyPipe->keyPressEvent(event);
}

void TestView::mkeyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        return;
    }
    keyPipe->keyReleaseEvent(event);
}

void TestView::test() {
    DebugI((int)Game->getSongChannel()->getTime())
}