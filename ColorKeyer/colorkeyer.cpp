#include "colorkeyer.h"
#include <QDebug>

using namespace cv;
using namespace std;

    const int MIN_OBJECT_AREA = 10*10;

    ColorKeyer::ColorKeyer() {
        QString fileString = "C:\\Users\\Besitzer\\Programming\\cpp\\AVPRG\\InteractiveMusicPlayground\\demo.mp3";
        //musicchips hinzufuegen
        musicChips.reserve(6);
        musicChips.push_back(MusicChip(MusicChip::SQUARE,MusicChip::RED,fileString));
        /*musicChips.push_back(MusicChip(MusicChip::SQUARE,MusicChip::GREEN,fileString));
        musicChips.push_back(MusicChip(MusicChip::SQUARE,MusicChip::YELLOW,fileString));
        musicChips.push_back(MusicChip(MusicChip::SQUARE,MusicChip::BLUE,fileString));
        musicChips.push_back(MusicChip(MusicChip::SQUARE,MusicChip::PURPLE,fileString));
        musicChips.push_back(MusicChip(MusicChip::HEXAGON,MusicChip::PURPLE,fileString));
        */
        EffectProcessor ep1;
        musicChips[0].setEffectProcessor(&ep1);
        /*musicChips[1].setEffectProcessor(&ep1);
        musicChips[2].setEffectProcessor(&ep1);
        musicChips[3].setEffectProcessor(&ep1);
        musicChips[4].setEffectProcessor(&ep1);
        musicChips[5].setEffectProcessor(&ep1);*/

        //Instanzvariablen setzen
        element = getStructuringElement(MORPH_CROSS,Size(8,8));
    }


    Mat ColorKeyer::maskColor(const Mat &input, MusicChip musicChip){

        cvtColor(input, input, CV_BGR2HSV);

        if(medianBlurValue > 0){
             medianBlur(input,input,medianBlurValue);
        }

        Mat output(input.rows, input.cols, CV_8UC1);
        inRange(input, musicChip.getRange().min, musicChip.getRange().max, output);

        return output;
    }

    Mat ColorKeyer::maskShape(const Mat input, MusicChip &musicChip, double minSize){

        Mat output = Mat::zeros(input.size(), CV_8UC1);
        vector<Vec4i> hierachy;
        vector<vector<Point>> contures;

        if(openValue > 0){
             morphologyEx(input, input, MORPH_OPEN, element, Point(-1,-1), openValue);
        }
        if(closeValue > 0){
            morphologyEx(input, input, MORPH_CLOSE, element, Point(-1,-1), closeValue);
        }

        findContours(input, contures, hierachy, RETR_LIST, CV_CHAIN_APPROX_TC89_KCOS);

        for(int i = 0; i < contures.size(); i++){
            vector<Point> approx;

            //prüfe ob konturen zu viereck passen
            approxPolyDP(contures[i], approx, 0.01*arcLength(contures[i], true), true);

            if(contourArea(contures[i]) >= minSize){
                if(musicChip.getConture() < 12 && approx.size() == musicChip.getConture()){
                    drawContours(output,contures,i,Scalar(255,255,255),CV_FILLED,8,noArray());
                    break;
                } else if (musicChip.getConture() >= 12 && approx.size() > musicChip.getConture()){
                    drawContours(output,contures,i,Scalar(255,255,255),CV_FILLED,8,noArray());
                    break;
                }
            }
        }
        return output;
    }

    Mat ColorKeyer::process(const Mat &input){
        
        Mat result = Mat::zeros(input.size(), CV_8UC1);

        for(int i = 0; i < musicChips.size(); i++){

           Mat m = maskShape(maskColor(input, musicChips[i]), musicChips[i], MIN_OBJECT_AREA);
           result = result | m;
           Point p = centerOfMass(m);

           if(!(p.x == 0 && p.y == 0)){
               //Display center of musicchip with the color of the musicchip
               circle(result, p, 9, Scalar(0,0,0),-1,8,0);
               musicChips[i].setCenter(p.x, p.y);
               musicChips[i].playTrack();
           }          
        }

        return result;
    }

    //berechne den Mittelpunkt
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

    void ColorKeyer::startProcessing(const VideoFormat& format){
        // Höhe: format.frameHeight()
        // Breite: format.frameWidth()
        // Framerate: format.framesPerSecond()
        // Pixelart: format.type() (CV_8UC1=Graustufen, CV_8UC3=BGR)
    }

    void ColorKeyer::setMedianBlurValue(int value){
        this->medianBlurValue = value;
    }

    void ColorKeyer::setOpenValue(int value){
        this->openValue = value;
    }

    void ColorKeyer::setCloseValue(int value){
        this->closeValue = value;
    }

