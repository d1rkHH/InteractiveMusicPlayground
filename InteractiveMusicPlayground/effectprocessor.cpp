#include "effectprocessor.h"
#include <QDebug>
#include <math.h>
#include <iostream>
EffectProcessor::EffectProcessor(float sampleRate)
    : AudioProcessor()
    , x1(0)
    , gain(0)
    , gainChange(0)
    , state(OFF)
{
    minGain = dB2gain(MIN_GAIN_DB);
    qDebug() << __FUNCTION__;
}

float EffectProcessor::dB2gain(float dB){
    return pow(10, dB/20);
}
float EffectProcessor::gain2dB(float gain){
    return 20*log(gain);
}

void EffectProcessor::startProcessing(const QAudioFormat &format){
    qDebug() << __FUNCTION__;
    this->format = format;
}

void EffectProcessor::process(float **input, float **output, int numFrames){
    if(state == FADEIN && gain >= 1){
        setState(ON);
    }
    if (state == FADEOUT && gain < minGain){
        setState(OFF);
    }
    //Never let the gain rise above 1
    gain = min(gain * gainChange, 1.0f);
    //std::cout << "State: " << state << " Gain: " << gain << " GainChange: " << gainChange << std::endl;

    for(int i = 0; i < numFrames; i++){
        output[0][i] = applyEffects(input[0][i]) * gain;
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
    qDebug() << __FUNCTION__;
}


float EffectProcessor::applyEffects(float input){
    return input;
}

void EffectProcessor::setState(State state){
    this->state = state;
    if (state == OFF){
        gain = 0;
        gainChange = 1;
    } else if (state == FADEIN){
        gainChange = 1.2;
        //If the gain is below the minGain (Equals 0), use minGain
        //Else, use the current gain value
        gain = max(gain,minGain);
    } else if (state == FADEOUT){
        gainChange = 0.95;
    } else if (state == ON){
        gain = 1;
        gainChange = 1;
    }
}

void EffectProcessor::active(){
    setState(FADEIN);
}

void EffectProcessor::off(){
    setState(FADEOUT);
}

void EffectProcessor::setChipCenter(Point center){
    qDebug() << __FUNCTION__;
    this->chipCenter = center;
}

float EffectProcessor::calculateEffectStrength(Point effect){
    qDebug() << __FUNCTION__;
    return 0.5;
}

void EffectProcessor::setEffectPositions(Point e1, Point e2, Point e3, Point e4){

}
