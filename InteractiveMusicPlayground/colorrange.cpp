#include "colorrange.h"

ColorRange ColorRange::YELLOW = ColorRange(Scalar(14,130,0), Scalar(32,255,255), "YELLOW");
ColorRange ColorRange::GREEN = ColorRange(Scalar(40,20,0), Scalar(75,255,255), "GREEN");
ColorRange ColorRange::RED = ColorRange(Scalar(0,50,0), Scalar(15,255,255), "RED");
ColorRange ColorRange::BLUE = ColorRange(Scalar(95,50,0), Scalar(105,255,255), "BLUE");
ColorRange ColorRange::PURPLE = ColorRange(Scalar(109,60,0), Scalar(130,255,255), "PURPLE");

ColorRange::ColorRange(Scalar min, Scalar max, QString name){
    this->min = min;
    this->max = max;
    this->name = name;
}

//Set a specific part of the ColorRange to a different value
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

QString ColorRange::getName(){
    return this->name;
}

