#ifndef MUSICCHIP
#define MUSICCHIP

#include <opencv2/opencv.hpp>
#include "audiofile.h"
#include "colorrange.h"

using namespace cv;

class MusicChip{

public:

    MusicChip();
    ~MusicChip(void);
    MusicChip(int contures, QString track);
    MusicChip(int contures, ColorRange &range, QString track);

    ColorRange getRange();
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
    static const int CIRCLE = 12;

    static ColorRange YELLOW;
    static ColorRange GREEN;
    static ColorRange RED;
    static ColorRange BLUE;
    static ColorRange PURPLE;


private:
    ColorRange *range;
    int contures;
    bool detection;
    QString track;
    Point center;
};


#endif // MUSICCHIP

