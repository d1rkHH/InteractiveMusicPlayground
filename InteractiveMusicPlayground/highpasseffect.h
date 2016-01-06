#ifndef HIGHPASSEFFECT_H
#define HIGHPASSEFFECT_H

#include "effect.h"

class HighPassEffect : public Effect
{
public:
    HighPassEffect();
    HighPassEffect(Point position);
    float apply(float input, float strength);
};

#endif // HIGHPASSEFFECT_H
