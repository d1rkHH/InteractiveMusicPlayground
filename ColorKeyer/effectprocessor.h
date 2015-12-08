#ifndef EFFECTPROCESSOR_H
#define EFFECTPROCESSOR_H

#include "audioprocessor.h"
#include <QAudioFormat>
#include <opencv2/opencv.hpp>

class EffectProcessor: public AudioProcessor{
public:
    EffectProcessor();
    void startProcessing(const QAudioFormat &format);
    void process(float **input, float **output, int numFrames);
    void stopProcessing();
    void setChipCenter(cv::Point center);
private:
    int x1;
    QAudioFormat format;
    cv::Point chipCenter;
    float calculateEffectStrength(cv::Point effect);
};

#endif // EFFECTPROCESSOR_H

