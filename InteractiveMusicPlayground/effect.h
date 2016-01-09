#ifndef EFFECT_H
#define EFFECT_H
#include <opencv2/opencv.hpp>

using namespace cv;

//Abstract class that can be subclassed to implement different sound effects/filters
class Effect
{
public:
    virtual float apply(float input, float strength) = 0;
    Point getPosition(){return position;}
protected:
    //Every effect has its position on the playground (x/y-Coordinates)
    //to calculate how strong an effect should be applied
    Point position;
};

#endif // EFFECT_H
