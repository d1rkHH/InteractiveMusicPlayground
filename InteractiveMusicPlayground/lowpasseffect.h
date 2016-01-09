#ifndef LOWPASSEFFECT_H
#define LOWPASSEFFECT_H

#include "effect.h"
#include "math.h"

//Uses averaging to apply a low pass filter on the audio output
class LowPassEffect : public Effect
{
public:
    LowPassEffect();
    LowPassEffect(Point position);
    float apply(float input, float strength);
    float lastInput;
    float lastInput2;
};

#endif // LOWPASSEFFECT_H
