#ifndef EFFECTPROCESSOR_H
#define EFFECTPROCESSOR_H

#include "audioprocessor.h"
#include <QAudioFormat>
#include <opencv2/opencv.hpp>
#include "effect.h"
#include "highpasseffect.h"

using namespace cv;

class EffectProcessor: public AudioProcessor{
public:
    enum State{OFF, FADEIN, ON, FADEOUT};
    EffectProcessor();
    void startProcessing(const QAudioFormat &format);
    void process(float **input, float **output, int numFrames);
    void stopProcessing();
    void setChipCenter(Point center);
    void active();
    void off();
    void setEffectPositions(Point e1, Point e2, Point e3, Point e4);
    void setState(State state);
    void setHeight(int height);
    void setWidth(int width);
    void setRatio(double ratio);
    float calculateEffectStrength(Point effect);
    float applyEffects(float input);
    Effect* chooseEffect();
    float dB2gain(float dB);
    float gain2dB(float gain);

private:
    State state;
    float gainChange;
    float gain;
    float minGain;
    const float MIN_GAIN_DB = -100;

    Effect* e1;
    Effect* e2;
    Effect* e3;
    Effect* e4;

    int height; //y
    int width; //x
    double ratio;

    QAudioFormat format;
    Point chipCenter;

};

#endif // EFFECTPROCESSOR_H

