//
// Created by admin on 2018/9/6.
//

#include <QtGui>
#include "TestView.h"
#include "defext.h"
#include "BeatmapDecoder.h"

TestView::TestView(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {
    setFixedSize(600,600);

    setAutoFillBackground(false);
    BeatmapDecoder decoder("D:\\Qt\\code\\qt_bb\\data\\324288 xi - ANiMA\\xi - ANiMA (Kuo Kyoka) [Starry's 4K Lv.15].osu");
    beatmap = new Beatmap;
    try {
        decoder.parse(*beatmap);
    } catch (DecodeException &e) {
        DebugS << "DecodeException : " << e.what();
    }

    string songpath = //"D:\\Qt\\code\\qt_bb\\data\\433128 Yui Sakakibara - Koigokoro to Beat!\\PURELYCATION.mp3";
    "D:\\Qt\\code\\qt_bb\\data\\324288 xi - ANiMA\\anima.mp3";
    channel = new EdpBassChannel(songpath);
    channel->play();
    keyPipe = new QTKeyPipe();
    keyPipe->setTimer(channel);
    frame = new KeyFrame(keyPipe, channel);

    playtimeData = new ManiaPlaytimeData();
    playtimeData->setTimer(channel);
    playtimeData->setMKeyFrame(frame);

    holder = new KeyHolder();
    frame->registerHolder(Qt::Key_A,holder);
    playtimeData->getKeys().push_back(holder);

    holder = new KeyHolder();
    frame->registerHolder(Qt::Key_S,holder);
    playtimeData->getKeys().push_back(holder);

    holder = new KeyHolder();
    frame->registerHolder(Qt::Key_K,holder);
    playtimeData->getKeys().push_back(holder);

    holder = new KeyHolder();
    frame->registerHolder(Qt::Key_L,holder);
    playtimeData->getKeys().push_back(holder);

    drawdata = new ManiaDrawdata(*beatmap);
    drawdata->prepare();
}

void TestView::animate() {
    /*playtimeData->update();
    drawdata->update(playtimeData->getFrameTime());*/
    repaint();
    /*playtimeData->endJudge();*/
}

void TestView::paintEvent(QPaintEvent *event) {
    playtimeData->update();
    drawdata->update(playtimeData->getFrameTime());


    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(event->rect(), QBrush(QColor(83, 158, 215)));


    QPen pen(QColor(40,44,53));
    int offset = 100;
    int width = 80;

    painter.save();
    painter.setPen(pen);
    painter.setBrush(QColor(40,44,53));
    painter.drawRect(QRect(offset, 0, width * 4, 600));
    painter.restore();


    painter.save();
    pen.setColor(QColor(255,255,255));
    painter.setPen(pen);
    for (int i = 0; i < 5; ++i) {
        painter.drawLine(offset + width * i, 0, offset + width * i, 600);
    }
    painter.drawLine(offset + width * 5, 0, offset + width * 5, static_cast<int>(playtimeData->getFrameTime() / 100));
    painter.restore();

    painter.save();
    pen.setColor(QColor(255,255,255));
    QLinearGradient linearGradient(0, 250, 0, 550);
    linearGradient.setColorAt(0, QColor(0, 0, 0, 0));
    linearGradient.setColorAt(1, QColor(255, 255, 255, 100));
    linearGradient.setSpread(QGradient::PadSpread);

    painter.setPen(pen);


    //painter.setBrush(QBrush(Qt::FDiagPattern));
    vector<ManiaDrawdataNode> &datas = drawdata->getDatas();

    //DebugI(datas.size())
    //DebugI(playtimeData->getFrameTime())

    int judgePosition = 550;
    int fieldHeight = 550;
    int noteHeight = 10;
    int holdPadding = 15;


    QLinearGradient linearGradient2(0, 0, 0, 200);
    linearGradient2.setColorAt(0, QColor(83, 158, 215, 0));
    linearGradient2.setColorAt(1, QColor(83, 158, 215, 255));
    linearGradient2.setSpread(QGradient::PadSpread);

    painter.setBrush(linearGradient2);

    ForEachLong(datas,it,vector<ManiaDrawdataNode>::iterator){
            if (it->line == 1||it->line == 2) {
                linearGradient2.setColorAt(0, QColor(83, 158, 215, 0));
                linearGradient2.setColorAt(1, QColor(83, 158, 215, 255));
            } else {
                linearGradient2.setColorAt(0, QColor(50, 130, 180, 0));
                linearGradient2.setColorAt(1, QColor(50, 130, 180, 255));
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
        }}

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
    painter.drawRect(QRectF(
            offset + width * 3,
            fieldHeight - noteHeight,
            width,
            noteHeight * 2
    ));


    painter.setBrush(linearGradient);
    for (int i = 0; i < 4; ++i) {
        if (playtimeData->getKeys()[i]->isPressed()) {
            painter.drawRect(QRect(offset + i * width, 0, width, 600));
        }
    }
    painter.restore();


    painter.end();


    playtimeData->endJudge();
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