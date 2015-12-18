#include "effectprocessor.h"
#include <QDebug>
#include <math.h>
EffectProcessor::EffectProcessor(): AudioProcessor(), x1(0), volume(0), gain(0), gainChange(0){
    qDebug() << __FUNCTION__;
}

void EffectProcessor::startProcessing(const QAudioFormat &format){
    qDebug() << __FUNCTION__;
    this->format = format;
}
inline float dB2gain(float dB){
    return pow(10, dB/20);
}
void EffectProcessor::process(float **input, float **output, int numFrames){
    if(volume == 1 && gain < 1){
        if(gain == 0){
            gain = 0.05;
        }
        float gainChange_dB = fabs(-100.f) / (1.5 * 44100);
        gainChange = dB2gain(gainChange_dB);
    } else  if (volume == 0 && gain > 0){
        float gainChange_dB = fabs(-100.f) / (1.5 * 44100);
        gainChange =  1/dB2gain(gainChange_dB);
    }
    qDebug() << __FUNCTION__;
    float effectStrength = calculateEffectStrength(cv::Point(0,0));
    for(int i = 0; i < numFrames; i++){
            output[0][i] = gain * (effectStrength * input[0][i] - effectStrength * x1);
            x1 = input[0][i];
    }
    // copy to other channels
    for(int c = 0; c < format.channelCount(); c++){
        for(int i = 0; i < numFrames; i++){
            output[c][i] = output[0][i];
        }
    }

    gain *= gainChange;
}



void EffectProcessor::stopProcessing(){
    qDebug() << __FUNCTION__;
}

void EffectProcessor::setVolume(float volume){
    this->volume = volume;
}

void EffectProcessor::setChipCenter(cv::Point center){
    qDebug() << __FUNCTION__;
    this->chipCenter = center;
}

float EffectProcessor::calculateEffectStrength(cv::Point effect){
    qDebug() << __FUNCTION__;
    return 0.5;
}
