#include "colorrange.h"

ColorRange ColorRange::RED = ColorRange(Scalar(170,120,50), Scalar(10,255,255), "RED");
ColorRange ColorRange::YELLOW = ColorRange(Scalar(15,100,170), Scalar(30,170,255), "YELLOW");
ColorRange ColorRange::GREEN = ColorRange(Scalar(60,30,40), Scalar(90,150,200), "GREEN");
ColorRange ColorRange::BLUE = ColorRange(Scalar(100,20,20), Scalar(115,150,200), "BLUE");
ColorRange ColorRange::PURPLE = ColorRange(Scalar(120,15,30), Scalar(140,200,200), "PURPLE");

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

