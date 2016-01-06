#include "effectprocessor.h"
#include <QDebug>
#include <math.h>
#include <iostream>
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
    Effect* effect = chooseEffect();
    float strength = calculateEffectStrength(effect->getPosition());
    return effect->apply(input, strength);
}

Effect* EffectProcessor::chooseEffect(){
    Point tf = Point(chipCenter.x, chipCenter.y * ratio);
    double distance_e1 = norm(e1->getPosition()-tf);
    double distance_e2 = norm(e2->getPosition()-tf);
    double distance_e3 = norm(e3->getPosition()-tf);
    double distance_e4 = norm(e4->getPosition()-tf);
    double min = std::min(std::min(distance_e1, distance_e2), std::min(distance_e3, distance_e4));
    if(min == distance_e2){
        //std::cout << "e2: " << min << std::endl;
        return e2;
    } else if(min == distance_e3){
        //std::cout << "e3: " << min << std::endl;
        return e3;
    } else if(min == distance_e4){
        //std::cout << "e4: " << min << std::endl;
        return e4;
    } else {
        //std::cout << "e1 (default): " << min << std::endl;
        return e1; //Default
    }
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
    float strength = 1 - scaled_distance;

    //DEBUG
    /*std::cout << " Effect Point (x,y)=" << effect.x << "," << effect.y
              << " Input Point (x,y)=" << chipCenter.x << "," << chipCenter.y
              << " Scaled Point (x,y)=" << p.x << "," << p.y
              << " dx=" << dx << " dy=" << dy
              << " max_distance=" << max_distance
              << " scaled distance=" << scaled_distance
              << " stength=" << strength << std::endl;
    */
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
    this->e2 = new HighPassEffect(Point(e2.x, e2.y*ratio));
    this->e3 = new HighPassEffect(Point(e3.x, e3.y*ratio));
    this->e4 = new HighPassEffect(Point(e4.x, e4.y*ratio));
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
