#include <QDebug>
#include <math.h>
#include "envelope.h"
const float MIN_GAIN_DB = -100;

inline float dB2gain(float dB){
    return pow(10, dB/20);
}
inline float gain2dB(float gain){
    return 20*log(gain);
}

Envelope::Envelope()
    : sampleRate(0), gain(0), state(OFF), releaseSeconds(0)
    , attackSeconds(0), decaySeconds(0)
    , sustain_dB(MIN_GAIN_DB), minGain_dB(MIN_GAIN_DB)
{
    sustainGain = minGain = dB2gain(MIN_GAIN_DB);
    setReleaseSeconds(0.5);
    setAttackSeconds(1);
}
void Envelope::setSampleRate(float sampleRate){
    this->sampleRate = sampleRate;
}
void Envelope::setReleaseSeconds(float seconds){
    this->releaseSeconds = seconds;
}
void Envelope::setAttackSeconds(float seconds){
    this->attackSeconds = seconds;
}
void Envelope::setDecaySeconds(float seconds){
    this->decaySeconds = seconds;
}
void Envelope::setSustain_dB(float sustain_dB){
    this->sustainGain = dB2gain(sustain_dB);
    this->sustain_dB = sustain_dB;
}

void Envelope::setState(State state){
    this->state = state;
    // avoid division by zero
    if (state == ATTACK && attackSeconds == 0){
        setState(DECAY);
    }
    else if (state == DECAY && decaySeconds == 0){
        setState(SUSTAIN);
    }
    else if (state == RELEASE && releaseSeconds == 0){
        setState(OFF);
    }
    else {
        if (state == OFF){
            gain = 0;
            qDebug() << "OFF";
        }
        if (state == ATTACK){
            float gainChange_dB = fabs(MIN_GAIN_DB) / (attackSeconds * sampleRate);
            gainChange = dB2gain(gainChange_dB);
            gain = minGain;
        }
        if (state == DECAY){
            gain = 1;
            float gainChange_dB = fabs(sustain_dB) / (decaySeconds * sampleRate);
            gainChange = 1/dB2gain(gainChange_dB);
        }
        if (state == RELEASE){
            float gainChange_dB = fabs(sustain_dB - MIN_GAIN_DB)/(sampleRate * releaseSeconds);
            gainChange =  1/dB2gain(gainChange_dB);
        }
        if (state == SUSTAIN){
            gain = sustainGain;
            gainChange = 1;
            qDebug() << "SUSTAIN";
        }
    }
}


float Envelope::process(float input){
    if(state == ATTACK && gain >= 1){
        setState(DECAY);
    }
    if (state == DECAY && gain < sustainGain){
        setState(SUSTAIN);
    }
    if (state == RELEASE && gain < minGain){
        setState(OFF);
    }
    gain *= gainChange;

    return gain * input;
}
