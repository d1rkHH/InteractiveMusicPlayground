#ifndef MUSICCHIP
#define MUSICCHIP

#include <opencv2/opencv.hpp>
#include "audiofile.h"

using namespace cv;

class MusicChip{
public:
    MusicChip(Scalar color, int contures, QString track);
    void setCenter(int x, int y);
private:
    Scalar color;
    int contures;
    QString track;
    Point center;
};

#endif // MUSICCHIP

