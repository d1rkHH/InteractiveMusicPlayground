#ifndef SOUNDCONTROL_H
#define SOUNDCONTROL_H

#include <QWidget>
#include "audioplayer.h"
#include "audiofile.h"
#include "effectprocessor.h"
#include <QFile>
#include <QAudioOutput>
#include <opencv2/opencv.hpp>

using namespace cv;

class SoundControl : public QObject
{
 Q_OBJECT

public:
    explicit SoundControl(QWidget *parent = 0);
    ~SoundControl();

public slots:
    void play(Point position);
    void stop();
    void applyEffects(Point position);
    void setTrack(QString track);
    void setEffects(Point e1, Point e2, Point e3, Point e4);

private:
    AudioFile* redTrack;
    AudioFile* yellowTrack;
    AudioFile* greenTrack;
    AudioFile* blueTrack;
    AudioFile* purpleTrack;
    AudioPlayer* redPlayer;
    AudioPlayer* yellowPlayer;
    AudioPlayer* greenPlayer;
    AudioPlayer* bluePlayer;
    AudioPlayer* purplePlayer;
    EffectProcessor* processor;
    AudioPlayer* getPlayer(QString playerName);
    AudioFile* getTrack(QString playerName);
};

#endif // SOUNDCONTROL_H


