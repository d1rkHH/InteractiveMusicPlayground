#ifndef COLORKEYER_H
#define COLORKEYER_H
#include <opencv2/opencv.hpp>
#include "videoprocessor.h"
#include "musicchip.h"
#include "colorrange.h"
#include "musicchip.h"

using namespace cv;

class ColorKeyer : public VideoProcessor
{
public:
    ColorKeyer();
    void startProcessing(const VideoFormat& format);
    cv::Mat process(const cv::Mat&source);
    void trackMusicChip(int currentChip, MusicChip chip, Mat threshold, Mat HSV, Mat input);
    void drawMusicChip(vector<MusicChip> chips,Mat &frame, Mat &temp, vector< vector<Point> > contours, vector<Vec4i> hierarchy);
    int RED = 5;
    int YELLOW = 21;
    int GREEN = 70;
    int BLUE = 100;
    int PURPLE = 135;



private:
    //Liste von MusicChips, die pro Frame abgefragt werden
    vector<MusicChip> musicChips;
    vector<Mat> outputs;
    Mat maskColor(const Mat &input, MusicChip musicChip);
    Point ColorKeyer::centerOfMass(Mat image);
    Mat ColorKeyer::maskShape(const Mat input, MusicChip &musicChip, double minSize);
    void ColorKeyer::setupGUI();
};

#endif // COLORKEYER_H
