#ifndef imageprocessor_H
#define imageprocessor_H
#include <opencv2/opencv.hpp>
#include "musicchip.h"
#include "colorrange.h"
#include "shapes.h"
#include "videoprocessor.h"
#include "videoformat.h"
#include "soundcontrol.h"
#include <QObject>
#include <QDebug>
#include <QDir>
#include <QString>

using namespace cv;

//Main class for all image processing tasks such as color detection and shape detection
class ImageProcessor :  public QObject, public VideoProcessor
{
    Q_OBJECT

public:
    ImageProcessor(SoundControl * soundControl, QObject* parent = 0);
    ~ImageProcessor();
    void startProcessing(const VideoFormat& format);
    Mat process(const Mat&source);
    //Setter
    void setMedianBlurValue(int value);
    void setOpenValue(int value);
    void setCloseValue(int value);
    void setMinChipSize(int value);
    void setDetectionTolerance(int value);
    void setPositionChangedTolerance(int value);
    void setPath(QString path);
    QString getPath();

signals:
    //Signal to communicate where the 4 points for the effects will be
    void declareEffectPositions(Point e1, Point e2, Point e3, Point e4);

private:
    //List of all musicChips which can get detected by the imageprocessor
    vector<MusicChip*> musicChips;
    //Structuring Element for Opening/Closing
    Mat element;
    //Value used for the medianBlur function
    int medianBlurValue;
    //Value used for the Opening function
    int openValue;
    //Value used for the Closing function
    int closeValue;
    //Minimum size a shape must have to get detected
    int minChipSize;
    //Number of frames a chip can be undetected without audio stopping
    int detectionTolerance;
    //Number of pixels a chip has to move until it gets registered as moving
    int positionChangedTolerance;
    //Path to where the resources are saved
    QString path;

    Mat maskColor(const Mat &input, MusicChip *musicChip);
    Mat maskShape(const Mat input, MusicChip *musicChip, Point &outputCenter);
    Point centerOfMass(vector<Point> contours);
};

#endif // imageprocessor_H
