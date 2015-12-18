#include "colorkeyer.h"
#include "soundcontrol.h"
#include "videoformat.h"
#include "musicchip.h"
#include <QDebug>
#include <QDir>

using namespace cv;
using namespace std;

ColorKeyer::ColorKeyer(SoundControl *soundControl, QObject *parent) : QObject(parent),minChipSize(100),element(getStructuringElement(MORPH_CROSS,Size(5,5))) {
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    //Create the musicChips
    MusicChip* redSquare = new MusicChip(Shapes::SQUARE,ColorRange::RED,QDir::currentPath()+"/XOXO.mp3");
    //MusicChip* blueSquare = new MusicChip(Shapes::SQUARE,ColorRange::BLUE,QDir::currentPath()+"/Alaska.mp3");

    //Put them into a vector
    musicChips.reserve(1);
    musicChips.push_back(redSquare);
    //musicChips.push_back(blueSquare);

    //Connect the SIGNALS and SLOTS
    //ColorKeyer
    QObject::connect(this, SIGNAL(declareEffectPositions(Point,Point,Point,Point)),soundControl, SLOT(setEffects(Point, Point, Point, Point)));
    //Chips
    for (int i = 0; i < musicChips.size(); i++){
        QObject::connect(musicChips[i], SIGNAL(on(Point)), soundControl, SLOT(play(Point)));
        QObject::connect(musicChips[i], SIGNAL(off()), soundControl, SLOT(stop()));
        QObject::connect(musicChips[i], SIGNAL(positionChanged(Point)), soundControl, SLOT(applyEffects(Point)));
        QObject::connect(musicChips[i], SIGNAL(passTrack(QString)), soundControl, SLOT(setTrack(QString)));
    }
}


Mat ColorKeyer::maskColor(const Mat &input, MusicChip *musicChip){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    cvtColor(input, input, CV_BGR2HSV);

    if(medianBlurValue > 0){
         medianBlur(input,input,medianBlurValue);
    }

    Mat output(input.rows, input.cols, CV_8UC1);
    inRange(input, musicChip->getRange().min, musicChip->getRange().max, output);

    return output;
}

Mat ColorKeyer::maskShape(const Mat input, MusicChip* musicChip, Point &outputCenter){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    Mat output = Mat::zeros(input.size(), CV_8UC1);
    vector<Vec4i> hierachy;
    vector<vector<Point>> contures;
    int contour = musicChip->getContour();

    if(openValue > 0){
         morphologyEx(input, input, MORPH_OPEN, element, Point(-1,-1), openValue);
    }
    if(closeValue > 0){
        morphologyEx(input, input, MORPH_CLOSE, element, Point(-1,-1), closeValue);
    }

    findContours(input, contures, hierachy, RETR_LIST, CV_CHAIN_APPROX_TC89_KCOS);

    for(int i = 0; i < contures.size(); i++){
        vector<Point> approx;
        approxPolyDP(contures[i], approx, 0.01*arcLength(contures[i], true), true);

        if(contourArea(contures[i]) >= minChipSize){
            if(contour < 12 && approx.size() == contour){
                //Triangle, Square, Pentagon, Hexagon, ...
                //Calculate center of Mass
                outputCenter = centerOfMass(contures[i]);
                //Draw the output image
                drawContours(output,contures,i,Scalar(255,255,255),CV_FILLED,8,noArray());
                break;
            } else if (contour >= 12 && approx.size() > contour){
                //Circle
                //Calculate center of Mass
                outputCenter = centerOfMass(contures[i]);
                //Draw the output image
                drawContours(output,contures,i,Scalar(255,255,255),CV_FILLED,8,noArray());
                break;
            }
        }
    }
    return output;
}

Mat ColorKeyer::process(const Mat &input){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    Mat result = Mat::zeros(input.size(), CV_8UC1);

    for(int i = 0; i < musicChips.size(); i++){
       //First, mask the color of the input as a function of the ColorRange from the musicchip
       //Pass this result to the maskShape function which detects the shape and returns
       //a binary matrix where white pixel represent the detected musicchip
       Point p(0,0);
       Mat m = maskShape(maskColor(input, musicChips[i]), musicChips[i], p);
       //If the matrix has at least as many white pixels as needed for the shape detection
       if(countNonZero(m) >= minChipSize){
            result = result | m;
            //If maskShape detects a shape, p contains the center of Mass
            //Display center of musicchip in output as black dot
            circle(result, p, 9, Scalar(0,0,0),-1,8,0);
            musicChips[i]->handleAudio(true, p);
            //It is very important to set the center after calling handleAudio
            //because handleAudio compares the passed point with the center-attribute
            //of the musicchip
            musicChips[i]->setCenter(p);
       } else {
            musicChips[i]->handleAudio(false);
       }
    }
    return result;
}

//berechne den Mittelpunkt
//TODO: Compare runtime with moments center of mass
Point ColorKeyer::centerOfMass(Mat mat){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;

    int sumx = 0;
    int sumy = 0;
    int count = 0;
    for(int x = 0; x < mat.cols; x++){
        for (int y = 0; y < mat.rows; y++){
            if (mat.at<uchar>(y,x) == 255){
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

Point ColorKeyer::centerOfMass(vector<Point> contours){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    Moments m = moments(contours,true);
    return Point((int)(m.m10/m.m00),(int)(m.m01/m.m00));
}

void ColorKeyer::startProcessing(const VideoFormat& format){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;

    int x = format.frameWidth();
    int y = format.frameHeight();
    emit declareEffectPositions(Point(0,0), Point(x,0), Point(0,y), Point(x,y));

    for(int i = 0; i < musicChips.size(); i++){
        musicChips[i]->sendTrack();
    }
}

void ColorKeyer::setMedianBlurValue(int value){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    this->medianBlurValue = value;
}

void ColorKeyer::setOpenValue(int value){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    this->openValue = value;
}

void ColorKeyer::setCloseValue(int value){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    this->closeValue = value;
}

void ColorKeyer::setMinChipSize(int value){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    this->minChipSize = value;
}

