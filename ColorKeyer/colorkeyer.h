#ifndef COLORKEYER_H
#define COLORKEYER_H
#include <opencv2/opencv.hpp>
#include "musicchip.h"
#include "colorrange.h"
#include "shapes.h"
#include "videoprocessor.h"
#include "soundcontrol.h"
#include <QObject>

using namespace cv;

class ColorKeyer :  public QObject, public VideoProcessor
{
    Q_OBJECT
public:
    ColorKeyer(SoundControl * soundControl, QObject* parent = 0);
    void startProcessing(const VideoFormat& format);
    cv::Mat process(const cv::Mat&source);
    void setMedianBlurValue(int value);
    void setOpenValue(int value);
    void setCloseValue(int value);
    void setMinChipSize(int value);

signals:
    void declareEffectPositions(Point e1, Point e2, Point e3, Point e4);

private:
    //Liste von MusicChips, die pro Frame abgefragt werden
    vector<MusicChip*> musicChips;
    Mat maskColor(const Mat &input, MusicChip *musicChip);
    Point ColorKeyer::centerOfMass(Mat mat);
    Point ColorKeyer::centerOfMass(vector<Point> contours);
    Mat ColorKeyer::maskShape(const Mat input, MusicChip *musicChip, Point &outputCenter);
    Mat element;
    int medianBlurValue;
    int openValue;
    int closeValue;
    int minChipSize; //TODO: Create UI scrollbar
};

#endif // COLORKEYER_H
