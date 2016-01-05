#ifndef SOUNDCONTROL_H
#define SOUNDCONTROL_H

#include <QWidget>
#include <QDebug>
#include "audioplayer.h"
#include "audiofile.h"
#include "effectprocessor.h"
#include <QFile>
#include <QAudioOutput>
#include <opencv2/opencv.hpp>
#include "musicchipplayer.h"
#include "musicchip.h"

using namespace cv;

class SoundControl : public QObject
{
 Q_OBJECT

public:
    SoundControl(QWidget *parent = 0);
    ~SoundControl();

public slots:
    void play(Point position);
    void stop();
    void applyEffects(Point position);
    void setTrack();
    void setEffects(Point e1, Point e2, Point e3, Point e4);

private:
    vector<MusicChipPlayer*> musicChipPlayers;
    MusicChipPlayer* redPlayer;
    MusicChipPlayer* bluePlayer;
    MusicChipPlayer* greenPlayer;
    MusicChipPlayer* yellowPlayer;
    MusicChipPlayer* purplePlayer;
    MusicChipPlayer* getPlayer(QString playerName);
};

#endif // SOUNDCONTROL_H


