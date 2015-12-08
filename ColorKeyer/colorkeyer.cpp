#include "colorkeyer.h"
#include <QDebug>;

using namespace cv;
using namespace std;

    const int MIN_OBJECT_AREA = 40*40;

    ColorKeyer::ColorKeyer() {

        //musicchips hinzufuegen
        musicChips.reserve(6);
        musicChips.push_back(MusicChip(MusicChip::SQUARE,MusicChip::RED,0));
        musicChips.push_back(MusicChip(MusicChip::SQUARE,MusicChip::GREEN,0));
        musicChips.push_back(MusicChip(MusicChip::SQUARE,MusicChip::YELLOW,0));
        musicChips.push_back(MusicChip(MusicChip::SQUARE,MusicChip::BLUE,0));
        musicChips.push_back(MusicChip(MusicChip::SQUARE,MusicChip::PURPLE,0));
        musicChips.push_back(MusicChip(MusicChip::HEXAGON,MusicChip::PURPLE,0));
    }


    Mat ColorKeyer::maskColor(const Mat &input, MusicChip musicChip){

        cvtColor(input, input, CV_BGR2HSV);
        Mat output(input.rows, input.cols, CV_8UC1);
        inRange(input, musicChip.getRange().min, musicChip.getRange().max, output);

        return output;
    }

    Mat ColorKeyer::maskShape(const Mat input, MusicChip &musicChip, double minSize){

        Mat output = Mat::zeros(input.size(), CV_8UC1);
        vector<Vec4i> hierachy;
        vector<vector<Point>> contures;

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

    void ColorKeyer::drawMusicChip(
            vector<MusicChip> chips,
	    	Mat &frame,
    		Mat &temp,
	    	vector< vector<Point> > contours,
	    	vector<Vec4i> hierarchy) {

        //zeichne konturen (gefüllt) sowie die mitte als blauer kreis
        for(int i =0; i < chips.size(); i++){
            cv::drawContours(frame, contours, i,Scalar(255,0,0),3,8,hierarchy);
            cv::circle(frame, chips[i].getCenter(), 5, Scalar(255,0,0), CV_FILLED);
        }

        //cv::drawContours(frame ,contours, 0, Scalar(0,0,0), 3/*CV_FILLED*/, 8, hierarchy);
        //Point p = centerOfMass(temp/*outputs[i]*/);
        //circle(frame, chip.getCenter(), 5, Scalar(255,0,0));
    }
    
    void ColorKeyer::trackMusicChip(int index, MusicChip mChip, Mat threshold, Mat HSV, Mat input){
    
    	//benötigte Komponenten initialisieren
    	vector <MusicChip> mChipList;
		Mat temp;
		threshold.copyTo(temp); //temp = threshold.clone();
		vector< vector<Point> > contours;
		vector<Vec4i> hierarchy;
		vector<Point> approx;
		//Konturen finden
        findContours(temp, contours, hierarchy,  CV_RETR_LIST /*CV_RETR_CCOMP*/, CV_CHAIN_APPROX_NONE/*_SIMPLE*/ );

		bool objectFound = false;
        if (hierarchy.size() > 0) {

            for (int i = 0; i >= 0; i = hierarchy[i][0]) {

                Moments moment = moments((cv::Mat)contours[i]);
                double area = moment.m00;

                if(area > MIN_OBJECT_AREA){

                     approxPolyDP(contours[i], approx, 0.01*arcLength(contours[i], true), true);
                     qDebug() << approx.size();
                    if(mChip.getConture() == MusicChip::SQUARE){
                        //prüfe ob konturen zu viereck passen
                        if(approx.size() == mChip.getConture()){
                            //setze neue Eigenschaften des erkannten Chips
                            //musicChips[index].setCenter(moment.m10/area, moment.m01/area);
                            //[index].setDetection(true);
                            objectFound = true;
                        }
                    }

                    if(objectFound){
                        MusicChip c;
                        c.setCenter(moment.m10/area, moment.m01/area);
                        c.setDetection(true);
                        mChipList.push_back(c);
                    }


                } else objectFound = false; //musicChips[index].setDetection(false);
            }//end for loop

        }

        if( /*musicChips[index].isDetected()*/ objectFound){
            //start music, apply filter
            //draw object location on screen
            drawMusicChip(/*musicChips[index]*/ mChipList, input, temp, contours, hierarchy);
        } else{
            //stop music etc.
        }
    }

    Mat ColorKeyer::process(const Mat &input){
        
        Mat element = getStructuringElement(MORPH_RECT,Size(8,8));
		Mat HSV;
		Mat threshold;
        Mat result = Mat::zeros(input.size(), CV_8UC1);

        for(int i = 0; i < musicChips.size(); i++){
           Mat m = maskShape(maskColor(input, musicChips[i]), musicChips[i], MIN_OBJECT_AREA);
           result = result | m;
           Point p = centerOfMass(m);
           if(!(p.x == 0 && p.y == 0)){
               //Display center of musicchip with the color of the musicchip
               circle(result, p, 9, Scalar(0,0,0),-1,8,0);
               //Get audiofile
               //Calculate effects by x and y coordinates
               //Play processed audiofile
           }

           //maskieren
           //cvtColor(input, HSV, CV_BGR2HSV);
           //medianBlur(input,input,3);
           //inRange(HSV, musicChips[i].getRange().min, musicChips[i].getRange().max, threshold);

           //filtern : opening und closing
           //morphologyEx(threshold, threshold, MORPH_OPEN, element, Point(-1,-1), 2);
           //morphologyEx(threshold, threshold, MORPH_CLOSE, element, Point(-1,-1), 2);



           //tracken
           //trackMusicChip(i, musicChips[i], threshold, HSV, threshold /*input*/);

           //result = result | threshold;
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

