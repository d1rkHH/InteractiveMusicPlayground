#ifndef COLORKEYER_H
#define COLORKEYER_H

#include "videoprocessor.h"

class ColorKeyer : public VideoProcessor
{
public:
    ColorKeyer();
    void startProcessing(const VideoFormat& format);
    cv::Mat process(const cv::Mat&source);
private:
    cv::Mat maskColor(const cv::Mat&source);
    cv::Point ColorKeyer::centerOfMass(cv::Mat& image);
};

#endif // COLORKEYER_H
