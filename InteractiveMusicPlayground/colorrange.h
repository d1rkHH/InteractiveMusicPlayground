#ifndef COLORRANGE_H
#define COLORRANGE_H
#include <opencv2/opencv.hpp>
#include <QString>
using namespace cv;

class ColorRange{
public:
    //Enum to access the single values and change them with setValue
    enum RangeIndex {MIN_HUE, MIN_SAT, MIN_VAL, MAX_HUE, MAX_SAT, MAX_VAL};

    //5 predefined colorranges
    static ColorRange YELLOW;
    static ColorRange GREEN;
    static ColorRange RED;
    static ColorRange BLUE;
    static ColorRange PURPLE;

    //Every ColorRange consists of two Scalars, one for the minimum
    //and one for the maximum values
    Scalar min;
    Scalar max;

    ColorRange(Scalar min, Scalar max, QString name);
    void setValue(RangeIndex index, int value);
    QString getName();
private:
    //Every ColorRange has a name to identify it
    //It should be equal to the variable name
    QString name;
};

#endif // COLORRANGE_H

