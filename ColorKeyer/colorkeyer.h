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
    void trackMusicChip(int currentChip, MusicChip chip, Mat threshold, Mat HSV, Mat input);
    void drawMusicChip(vector<MusicChip> chips,Mat &frame, Mat &temp, vector< vector<Point> > contours, vector<Vec4i> hierarchy);
    int numberOfMusicChips;
    int RED = 5;
    int YELLOW = 21;
    int GREEN = 70;
    int BLUE = 100;
    int PURPLE = 135;



private:
    //Liste von MusicChips, die pro Frame abgefragt werden
    vector<MusicChip> musicChips;
    vector<cv::Mat> outputs;
    cv::Mat maskColor(const cv::Mat &input, MusicChip musicChip);
    cv::Point ColorKeyer::centerOfMass(cv::Mat image);
    cv::Mat ColorKeyer::maskShape(const Mat input, MusicChip &musicChip, int shape, double minSize);
};

#endif // COLORKEYER_H
