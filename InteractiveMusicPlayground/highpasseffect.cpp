#include "highpasseffect.h"

HighPassEffect::HighPassEffect()
{
}

HighPassEffect::HighPassEffect(Point position){
    this->position = position;
}

float HighPassEffect::apply(float input, float strength){
    return input * strength;
}
