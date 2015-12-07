#ifndef MUSICCHIP
#define MUSICCHIP

#include <opencv2/opencv.hpp>
#include "audiofile.h"

using namespace cv;

class MusicChip{

public:

    MusicChip();
    ~MusicChip(void);
    MusicChip(int contures, QString track);

    void setHSVmin(Scalar min);
    void setHSVmax(Scalar max);
    Scalar getHSVmin();
    Scalar getHSVmax();
    void setCenter(int x, int y);
    Point getCenter();
    int getConture();
    void setDetection(bool detec);
    bool isDetected();
    //Konstanten fuer moegliche Formen auf dem MusicChip
    static const int TRIANGLE = 3;
    static const int PENTAGON = 5;
    static const int SQUARE = 4;
    static const int HEXAGON = 6;
    static const int CIRCLE = -1;

private:
    Scalar min;
    Scalar max;
    int contures;
    bool detection;
    QString track;
    Point center;
};


#endif // MUSICCHIP

