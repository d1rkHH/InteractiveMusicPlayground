#include "effectprocessor.h"

EffectProcessor::EffectProcessor(): AudioProcessor(), x1(0){

}

void EffectProcessor::startProcessing(const QAudioFormat &format){
    this->format = format;
}

void EffectProcessor::process(float **input, float **output, int numFrames){
    float effectStrength = calculateEffectStrength(cv::Point(0,0));
    for(int i = 0; i < numFrames; i++){
            output[0][i] = effectStrength * input[0][i] - effectStrength * x1;
            x1 = input[0][i];
    }
    // copy to other channels
    for(int c = 0; c < format.channelCount(); c++){
        for(int i = 0; i < numFrames; i++){
            output[c][i] = output[0][i];
        }
    }
}

void EffectProcessor::stopProcessing(){

}

void EffectProcessor::setChipCenter(cv::Point center){
    this->chipCenter = center;
}

float EffectProcessor::calculateEffectStrength(cv::Point effect){
    return 0.5;
}
