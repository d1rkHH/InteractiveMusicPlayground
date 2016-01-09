#include "effectprocessor.h"
#include <QDebug>
#include <math.h>
EffectProcessor::EffectProcessor()
    : AudioProcessor()
    , gain(0)
    , gainChange(0)
    , state(OFF)
    , height(0)
    , width(0)
    , ratio(0)
{
    minGain = dB2gain(MIN_GAIN_DB);
}

EffectProcessor::~EffectProcessor(){
    delete e1;
    delete e2;
    delete e3;
    delete e4;
}

float EffectProcessor::dB2gain(float dB){
    return pow(10, dB/20);
}
float EffectProcessor::gain2dB(float gain){
    return 20*log(gain);
}

void EffectProcessor::startProcessing(const QAudioFormat &format){
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

    for(int i = 0; i < numFrames; i++){
        output[0][i] = applyEffects(input[0][i]) * gain;

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


//Apply an effect to the audio input
//Because apply also sets some internal values
//it has to be called for every effect all the time
//The difference is just which value gets returned
float EffectProcessor::applyEffects(float input){
    Effect* effect = chooseEffect();
    float strength = calculateEffectStrength(effect->getPosition());
    if(effect == e1){
        e2->apply(input, 0);
        e3->apply(input, 0);
        e4->apply(input, 0);
        return e1->apply(input, strength);
    } else if (effect == e2){
        e1->apply(input, 0);
        e3->apply(input, 0);
        e4->apply(input, 0);
        return e2->apply(input, strength);
    } else if (effect == e3){
        e1->apply(input, 0);
        e2->apply(input, 0);
        e4->apply(input, 0);
        return e3->apply(input, strength);
    } else if (effect == e4){
        e1->apply(input, 0);
        e2->apply(input, 0);
        e3->apply(input, 0);
        return e4->apply(input, strength);
    } else {
        return input;
    }
}

//Choose the active effect by calculating which effect is closest to the musicchip
Effect* EffectProcessor::chooseEffect(){
    Point tf = Point(chipCenter.x, chipCenter.y * ratio);
    double distance_e1 = norm(e1->getPosition()-tf);
    double distance_e2 = norm(e2->getPosition()-tf);
    double distance_e3 = norm(e3->getPosition()-tf);
    double distance_e4 = norm(e4->getPosition()-tf);
    double min = std::min(std::min(distance_e1, distance_e2), std::min(distance_e3, distance_e4));
    if(min == distance_e2){
        return e2;
    } else if(min == distance_e3){
        return e3;
    } else if(min == distance_e4){
        return e4;
    } else {
        return e1; //Default
    }
}

void EffectProcessor::setState(State state){
    this->state = state;
    if (state == OFF){
        gain = 0;
        gainChange = 1;
    } else if (state == FADEIN){
        gainChange = 1.2f;
        //If the gain is below the minGain (Equals 0), use minGain
        //Else, use the current gain value
        gain = max(gain,minGain);
    } else if (state == FADEOUT){
        gainChange = 0.95f;
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
    this->chipCenter = center;
}

float EffectProcessor::calculateEffectStrength(Point effect){
    //At first, make x and y scale equally bis multiplying the y-value with
    //the aspect ratio of x and y
    Point p = Point(chipCenter.x, chipCenter.y * ratio);
    //After this, calculate the distance for each the x and the y coordinate
    int dx = abs(effect.x-p.x);
    int dy = abs(effect.y-p.y);
    //Get the maximum value of both
    int max_distance = std::max(dx, dy);
    //Scale the value down to 0..1
    //If the value gets above 1 (because the point is further than 50% of the
    //screen away (should never happen), use 1 instead)
    float scaled_distance = std::min((float)(max_distance)/((float)(width)/2),1.0f);
    //Calculate the strength by this value (linear)
    //TODO: Change to logarithmic scale
    float strength = std::max(std::min(1.4*(1 - scaled_distance-0.2),1.0),0.0);
    //alternative functions:
    //float strength = std::min(0.75*pow(1-scaled_distance)+0.1,3),1.0);
    //float strength = -2*pow(1-scaled_distance,3)+3.125*pow(1-scaled_distance,2)-0.042*(1-scaled_distance);
    return strength;
}

//The 4 effect positions mark the outer lines of the playground
void EffectProcessor::setEffectPositions(Point e1, Point e2, Point e3, Point e4){
    //At first, calculate the height and width, also the aspect ratio
    this->height = std::max(std::max(e1.y, e2.y), std::max(e3.y, e4.y));
    this->width = std::max(std::max(e1.x, e2.x), std::max(e3.x, e4.x));
    this->ratio = (double)(width)/(double)(height);
    //After that, create Effects, but with y-Coordinate scaled up
    //so the coordinate system is proportional
    this->e1 = new HighPassEffect(Point(e1.x, e1.y*ratio));
    this->e2 = new LowPassEffect(Point(e2.x, e2.y*ratio));
    this->e3 = new DelayEffect(Point(e3.x, e3.y*ratio));
    this->e4 = new DelayEffect(Point(e4.x, e4.y*ratio));
}

void EffectProcessor::setHeight(int height){
    this->height = height;
}

void EffectProcessor::setWidth(int width){
    this->width = width;
}

void EffectProcessor::setRatio(double ratio){
    this->ratio = ratio;
}
