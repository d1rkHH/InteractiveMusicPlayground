#ifndef COLORRANGE_H
#define COLORRANGE_H
#include <opencv2/opencv.hpp>
using namespace cv;

class ColorRange{
public:
    enum RangeIndex {MIN_HUE, MIN_SAT, MIN_VAL, MAX_HUE, MAX_SAT, MAX_VAL};

    Scalar min;
    Scalar max;

    ColorRange();
    ColorRange(Scalar min, Scalar max);
    void setValue(RangeIndex index, int value);

    static ColorRange A;
};

#endif // COLORRANGE_H

