#ifndef DELAYEFFECT_H
#define DELAYEFFECT_H
#include "ringbuffer.h"
#include "effect.h"

//DelayEffect uses a Ringbuffer to add
//an delay-effect to the audio output
class DelayEffect : public Effect
{
public:
    DelayEffect();
    DelayEffect(Point position);
    float apply(float input, float strength);
    const float delaySeconds = 0.08f;
    float sampleRate;
    RingBuffer buffer;

};

#endif // DELAYEFFECT_H
