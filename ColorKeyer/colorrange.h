#ifndef COLORRANGE_H
#define COLORRANGE_H
#include <opencv2/opencv.hpp>
#include <QString>
using namespace cv;

class ColorRange{
public:
    enum RangeIndex {MIN_HUE, MIN_SAT, MIN_VAL, MAX_HUE, MAX_SAT, MAX_VAL};

    static ColorRange YELLOW;
    static ColorRange GREEN;
    static ColorRange RED;
    static ColorRange BLUE;
    static ColorRange PURPLE;

    Scalar min;
    Scalar max;

    ColorRange();
    ColorRange(Scalar min, Scalar max, QString name);
    void setValue(RangeIndex index, int value);
    QString getName(){return name;}
private:
    QString name;
};

#endif // COLORRANGE_H

