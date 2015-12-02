#include "colorkeyer.h"

using namespace cv;


ColorKeyer::ColorKeyer()
{
    namedWindow("Control",WINDOW_AUTOSIZE);
    createTrackbar("Rot Schwellwert", "Control", &RED, 179, 0);
    createTrackbar("Gelb Schwellwert", "Control", &YELLOW, 179, 0);
    createTrackbar("Gruen Schwellwert", "Control", &GREEN, 179, 0);
    createTrackbar("Tuerkis Schwellwert", "Control", &BLUE, 179, 0);
    createTrackbar("Blau Schwellwert", "Control", &PURPLE, 179, 0);
}

void ColorKeyer::startProcessing(const VideoFormat& format){
    // Höhe: format.frameHeight()
    // Breite: format.frameWidth()
    // Framerate: format.framesPerSecond()
    // Pixelart: format.type() (CV_8UC1=Graustufen, CV_8UC3=BGR)
}

Mat ColorKeyer::maskColor(const Mat input, int hue){
    cvtColor(input, input, CV_BGR2HSV);
    Mat output(input.rows, input.cols, CV_8UC1);

    Scalar from(hue < 5 ? 0 : hue - 5, 50, 50);
    Scalar to(hue > 174 ? 179 : hue + 5, 255, 255);
    inRange(input, from, to, output);

    return output;
}

Mat ColorKeyer::maskShape(const Mat input, int shape, double minSize){
    vector<Vec4i> hierachy;
    vector<vector<Point>> contures;
    Mat output = Mat::zeros(input.size(), CV_8UC1);
    findContours(input, contures, hierachy, RETR_LIST, CV_CHAIN_APPROX_TC89_KCOS);
    for(int i = 0; i < contures.size(); i++){
        vector<Point> approx;
        approxPolyDP(contures[i], approx, 0.01*arcLength(contures[i], true), true);
        if(contourArea(contures[i]) >= minSize && approx.size() == shape){
            drawContours(output,contures,i,Scalar(255,255,255),CV_FILLED,8,noArray());
            break;
        }
    }
    return output;
}

Mat ColorKeyer::process(const Mat &input){

    //Divide input in 6 color spaces
    Mat red = maskColor(input, RED);
    Mat yellow = maskColor(input, YELLOW);
    Mat green = maskColor(input, GREEN);
    Mat blue = maskColor(input, BLUE);
    Mat purple = maskColor(input, PURPLE);

    red = maskShape(red, SQUARE, 100);

    if(!red.empty()){
        Point p = centerOfMass(red);
        circle(red, p, 5, Scalar(0,0,0),-1,8,0);
        qDebug() << "X: " << p.x << " Y: " << p.y;
    }

    return red;
}

Point ColorKeyer::centerOfMass(Mat image){
    int sumx = 0;
    int sumy = 0;
    int count = 0;
    for(int x = 0; x < image.cols; x++){
        for (int y = 0; y < image.rows; y++){
            if (image.at<uchar>(y,x) == 255){
                sumx += x;
                sumy += y;
                count++;
            }
        }
    }
    if (count > 0){
        return Point(sumx/count, sumy/count);
    }
    else{
        return Point(0,0);
    }
}
