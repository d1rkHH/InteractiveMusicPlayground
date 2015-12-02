#ifndef COLORKEYER_H
#define COLORKEYER_H
#include <opencv2/opencv.hpp>
#include "videoprocessor.h"
#include "musicchip.h"

using namespace cv;

class ColorKeyer : public VideoProcessor
{
public:
    ColorKeyer();
    void startProcessing(const VideoFormat& format);
    cv::Mat process(const cv::Mat&source);
    int RED = 5;
    int YELLOW = 21;
    int GREEN = 70;
    int BLUE = 100;
    int PURPLE = 135;

    const int TRIANGLE = 3;
    const int SQUARE = 4;
    const int HEXAGON = 6;
    const int CIRCLE = -1;

private:
    cv::Mat maskColor(const cv::Mat input, int color);
    cv::Point ColorKeyer::centerOfMass(cv::Mat image);
    cv::Mat ColorKeyer::maskShape(const Mat input, int shape, double minSize);
};

#endif // COLORKEYER_H
