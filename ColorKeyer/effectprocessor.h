#ifndef EFFECTPROCESSOR_H
#define EFFECTPROCESSOR_H

#include "audioprocessor.h"
#include <QAudioFormat>

class EffectProcessor: public AudioProcessor{
public:
    EffectProcessor();
    void startProcessing(const QAudioFormat &format);
    void process(float **input, float **output, int numFrames);
    void stopProcessing();
    void setDoLowPass(bool doLowPass);
private:
    int x1;
    bool doLowPass;
    QAudioFormat format;
};

#endif // EFFECTPROCESSOR_H

