#include "lowpasseffect.h"

LowPassEffect::LowPassEffect()
    : lastInput(0), lastInput2(0)
{}

LowPassEffect::LowPassEffect(Point position)
    : lastInput(0), lastInput2(0){
    this->position = position;
}

float LowPassEffect::apply(float input, float strength){
    float output = strength * ((input + lastInput + lastInput2)/3) + (1-strength) * input;
    lastInput2 = lastInput;
    lastInput = input;
    return output;
}
