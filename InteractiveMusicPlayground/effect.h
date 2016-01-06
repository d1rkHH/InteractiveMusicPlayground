#ifndef EFFECT_H
#define EFFECT_H
#include <opencv2/opencv.hpp>

using namespace cv;

class Effect
{
public:
    virtual float apply(float input, float strength) = 0;
    Point getPosition(){return position;}
protected:
    Point position;
};

#endif // EFFECT_H
