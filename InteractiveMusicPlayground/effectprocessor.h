#ifndef EFFECTPROCESSOR_H
#define EFFECTPROCESSOR_H

#include "audioprocessor.h"
#include <QAudioFormat>
#include <opencv2/opencv.hpp>

using namespace cv;

class EffectProcessor: public AudioProcessor{
public:
    enum State{OFF, FADEIN, ON, FADEOUT};
    EffectProcessor(float sampleRate);
    void startProcessing(const QAudioFormat &format);
    void process(float **input, float **output, int numFrames);
    void stopProcessing();
    void setChipCenter(Point center);
    void active();
    void off();
    void setEffectPositions(Point e1, Point e2, Point e3, Point e4);
    void setState(State state);

private:
    State state;
    float gainChange;
    float gain;
    float minGain;
    const float MIN_GAIN_DB = -100;

    int x1;

    QAudioFormat format;
    Point chipCenter;
    float calculateEffectStrength(Point effect);
    float applyEffects(float input);
    float dB2gain(float dB);
    float gain2dB(float gain);
};

#endif // EFFECTPROCESSOR_H

