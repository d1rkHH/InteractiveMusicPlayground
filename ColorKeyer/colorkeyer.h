#ifndef COLORKEYER_H
#define COLORKEYER_H
#include <opencv2/opencv.hpp>
#include "videoprocessor.h"
#include "musicchip.h"
#include "colorrange.h"
#include "musicchip.h"
#include "audioplayer.h"
#include "effectprocessor.h"

using namespace cv;

class ColorKeyer : public VideoProcessor
{
public:
    ColorKeyer();
    void startProcessing(const VideoFormat& format);
    cv::Mat process(const cv::Mat&source);
    void setMedianBlurValue(int value);
    void setOpenValue(int value);
    void setCloseValue(int value);
    EffectProcessor effectProcessor; //TODO: Auslagern

private:
    //Liste von MusicChips, die pro Frame abgefragt werden
    vector<MusicChip> musicChips;
    Mat maskColor(const Mat &input, MusicChip musicChip);
    Point ColorKeyer::centerOfMass(Mat image);
    Mat ColorKeyer::maskShape(const Mat input, MusicChip &musicChip, double minSize);
    Mat element;
    int medianBlurValue;
    int openValue;
    int closeValue;
    AudioPlayer audioPlayer;
};

#endif // COLORKEYER_H
