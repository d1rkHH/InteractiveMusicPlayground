#include "colorrange.h"

ColorRange::ColorRange(Scalar min, Scalar max){
    this->min = min;
    this->max = max;
}

ColorRange::ColorRange(){

}

void ColorRange::setValue(RangeIndex index, int value){
    switch(index){
        case MIN_HUE:
            this->min[0] = value;
            break;
        case MIN_SAT:
            this->min[1] = value;
            break;
        case MIN_VAL:
            this->min[2] = value;
            break;
         case MAX_HUE:
            this->max[0] = value;
            break;
         case MAX_SAT:
            this->max[1] = value;
            break;
         case MAX_VAL:
            this->max[2] = value;
            break;
    }
}

