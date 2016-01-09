#ifndef SOUNDCONTROL_H
#define SOUNDCONTROL_H

#include <QDebug>
#include "audioplayer.h"
#include "audiofile.h"
#include "effectprocessor.h"
#include <QAudioOutput>
#include <opencv2/opencv.hpp>
#include "musicchipplayer.h"
#include "musicchip.h"

using namespace cv;

//This class is responsible for managing the sound
//It gets called via signal/slot-mechanism from
//the ImageProcessor.
class SoundControl : public QObject
{
 Q_OBJECT

public:
    SoundControl(QObject *parent = 0);
    ~SoundControl();
    void start();

public slots:
    void play(Point position);
    void stop();
    void applyEffects(Point position);
    void setTrack();
    void setEffects(Point e1, Point e2, Point e3, Point e4);

private:
    vector<MusicChipPlayer*> musicChipPlayers;
    bool started;
    MusicChipPlayer* getPlayer(QString playerName);
};

#endif // SOUNDCONTROL_H


