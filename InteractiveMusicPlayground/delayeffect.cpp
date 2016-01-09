#include "delayeffect.h"

DelayEffect::DelayEffect()
    : sampleRate(44100) {}

DelayEffect::DelayEffect(Point position)
    : sampleRate(44100)
{
    this->position = position;
    buffer.resize(delaySeconds * sampleRate);
}

float DelayEffect::apply(float input, float strength){
    float value = buffer.readWithDelay(delaySeconds * sampleRate);
    buffer.write(input);
    return input + strength * value;
}
