#include "effectprocessor.h"

EffectProcessor::EffectProcessor(): AudioProcessor(), x1(0){

}

void EffectProcessor::startProcessing(const QAudioFormat &format){
    this->format = format;
}

void EffectProcessor::process(float **input, float **output, int numFrames){
    for(int i = 0; i < numFrames; i++){
        if(doLowPass){
            output[0][i] = 0.5 * input[0][i] - 0.5 * x1;
        } else {
            output[0][i] = input[0][i];
        }
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

void EffectProcessor::setDoLowPass(bool doLowPass){
    this->doLowPass = doLowPass;
}
