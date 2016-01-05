#include "imageprocessor.h"

ImageProcessor::ImageProcessor(SoundControl *soundControl, QObject *parent)
    : QObject(parent)
    , minChipSize(100)
    , element(getStructuringElement(MORPH_CROSS,Size(5,5)))
{
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    //Create the musicChips
    QString path = "C:\\Users\\Besitzer\\Programming\\cpp\\AVPRG\\InteractiveMusicPlayground\\sounds\\";
    MusicChip* redSquare = new MusicChip(Shapes::SQUARE,ColorRange::RED, path + "truecolors.mp3");
    MusicChip* blueSquare = new MusicChip(Shapes::SQUARE,ColorRange::PURPLE, path + "fairytale.mp3");

    //Put them into a vector
    musicChips.reserve(2);
    musicChips.push_back(redSquare);
    musicChips.push_back(blueSquare);

    //Connect the SIGNALS and SLOTS
    //ImageProcessor
    QObject::connect(this, SIGNAL(declareEffectPositions(Point,Point,Point,Point)),soundControl, SLOT(setEffects(Point, Point, Point, Point)));
    //MusicChips
    for (uint i = 0; i < musicChips.size(); i++){
        QObject::connect(musicChips[i], SIGNAL(on(Point)), soundControl, SLOT(play(Point)));
        QObject::connect(musicChips[i], SIGNAL(off()), soundControl, SLOT(stop()));
        QObject::connect(musicChips[i], SIGNAL(positionChanged(Point)), soundControl, SLOT(applyEffects(Point)));
        QObject::connect(musicChips[i], SIGNAL(passTrack()), soundControl, SLOT(setTrack()));
    }
}

//This function contains setup work that only need to be done once at the start
void ImageProcessor::startProcessing(const VideoFormat& format){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;

    int x = format.frameWidth();
    int y = format.frameHeight();
    emit declareEffectPositions(Point(0,0), Point(x,0), Point(0,y), Point(x,y));

    for(uint i = 0; i < musicChips.size(); i++){
        //SendTrack emits passTrack
        qDebug() << "Send track for chip" << i;
        musicChips[i]->sendTrack();
    }
}

//Central method that gets called for every input frame. It returns a binary image
//containing all detected musicchips. This function calls handleAudio for every
//musicchip inside the vector musicChips. This way, if a musicChip gets detected,
//audio will play
Mat ImageProcessor::process(const Mat &input){
    Mat result = Mat::zeros(input.size(), CV_8UC1);

    for(uint i = 0; i < musicChips.size(); i++){
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

//Masks the input for the colorRange of the given MusicChip
//Returns a binary matrix where every pixel within the ColorRange is white
Mat ImageProcessor::maskColor(const Mat &input, MusicChip *musicChip){
    cvtColor(input, input, CV_BGR2HSV);

    if(medianBlurValue > 0){
         medianBlur(input,input,medianBlurValue);
    }

    Mat output(input.rows, input.cols, CV_8UC1);
    inRange(input, musicChip->getRange().min, musicChip->getRange().max, output);

    return output;
}

//Masks the input for the shape of the given MusicChip
//Uses an approximation algorithm to detect geometric shapes
//Returns a black matrix if no shape is found
//Returns a filled white shape on a black matrix if the shape is found
//stops after finding the first shape
Mat ImageProcessor::maskShape(const Mat input, MusicChip* musicChip, Point &outputCenter){
    Mat output = Mat::zeros(input.size(), CV_8UC1);
    vector<vector<Point>> contours;
    uint contour = musicChip->getContour();

    if(openValue > 0){
         morphologyEx(input, input, MORPH_OPEN, element, Point(-1,-1), openValue);
    }
    if(closeValue > 0){
        morphologyEx(input, input, MORPH_CLOSE, element, Point(-1,-1), closeValue);
    }

    findContours(input, contours, RETR_LIST, CV_CHAIN_APPROX_TC89_KCOS);

    for(uint i = 0; i < contours.size(); i++){
        vector<Point> approx;
        approxPolyDP(contours[i], approx, 0.01*arcLength(contours[i], true), true);

        if(contourArea(contours[i]) >= minChipSize){
            if(contour < 12 && approx.size() == contour){
                //Triangle, Square, Pentagon, Hexagon, ...
                //Calculate center of Mass
                outputCenter = centerOfMass(contours[i]);
                //Draw the output image
                drawContours(output,contours,i,Scalar(255,255,255),CV_FILLED,8,noArray());
                break;
            } else if (contour >= 12 && approx.size() > contour){
                //Circle
                //Calculate center of Mass
                outputCenter = centerOfMass(contours[i]);
                //Draw the output image
                drawContours(output,contours,i,Scalar(255,255,255),CV_FILLED,8,noArray());
                break;
            }
        }
    }
    return output;
}

Point ImageProcessor::centerOfMass(vector<Point> contours){
    Moments m = moments(contours,true);
    return Point((int)(m.m10/m.m00),(int)(m.m01/m.m00));
}

void ImageProcessor::setMedianBlurValue(int value){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    this->medianBlurValue = value;
}

void ImageProcessor::setOpenValue(int value){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    this->openValue = value;
}

void ImageProcessor::setCloseValue(int value){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    this->closeValue = value;
}

void ImageProcessor::setMinChipSize(int value){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    this->minChipSize = value;
}

