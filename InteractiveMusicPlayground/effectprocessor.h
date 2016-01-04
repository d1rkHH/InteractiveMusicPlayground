#ifndef EFFECTPROCESSOR_H
#define EFFECTPROCESSOR_H

#include "audioprocessor.h"
#include <QAudioFormat>
#include <opencv2/opencv.hpp>

using namespace cv;

class EffectProcessor: public AudioProcessor{
public:
    EffectProcessor();
    void startProcessing(const QAudioFormat &format);
    void process(float **input, float **output, int numFrames);
    void stopProcessing();
    void setChipCenter(Point center);
    void setVolume(float volume);
private:
    float volume;
    float gainChange;
    float gain;
    int x1;
    QAudioFormat format;
    cv::Point chipCenter;
    float calculateEffectStrength(Point effect);
};

#endif // EFFECTPROCESSOR_H

