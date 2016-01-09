#ifndef HIGHPASSEFFECT_H
#define HIGHPASSEFFECT_H

#include "effect.h"
#include "math.h"

//Apply a high pass filter/effect to the audio output
class HighPassEffect : public Effect
{
public:
    HighPassEffect();
    HighPassEffect(Point position);
    float apply(float input, float strength);
    float lastInput;
    float lastOutput;
};

#endif // HIGHPASSEFFECT_H
