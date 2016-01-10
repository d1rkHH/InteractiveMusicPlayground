#include "highpasseffect.h"

HighPassEffect::HighPassEffect()
: lastInput(0), lastOutput(0){
}

HighPassEffect::HighPassEffect(Point position)
: lastInput(0), lastOutput(0){
    this->position = position;
}

/* Apply a highpass filter on the input. The input
 * and the output get merged based on the strength
 * where a strengh of 1 means, 100% of the applied highpass
 * will be returned, 0.5 means 50% of the high pass will
 * get averaged with 50% of the input, and 0 means
 * the input will get returned
 */
float HighPassEffect::apply(float input, float strength){
    lastOutput = 0.9f * (lastOutput + input - lastInput);
    float output = lastOutput * strength + input * (1-strength);
    lastInput = input;
    return output;
}
