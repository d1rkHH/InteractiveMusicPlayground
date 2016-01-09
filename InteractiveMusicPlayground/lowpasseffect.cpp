#include "lowpasseffect.h"

LowPassEffect::LowPassEffect()
    : lastInput(0), lastInput2(0)
{}

LowPassEffect::LowPassEffect(Point position)
    : lastInput(0), lastInput2(0){
    this->position = position;
}

float LowPassEffect::apply(float input, float strength){
    float output = (input + lastInput + lastInput2)/3;
    lastInput2 = lastInput;
    lastInput = input;
    return output;
}
