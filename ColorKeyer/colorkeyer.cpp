#include "colorkeyer.h"
#include "musicchip.h"
#include <QDebug>
using namespace cv;
using namespace std;
    int H_MIN = 0;
    int H_MAX = 256;
    int S_MIN = 0;
    int S_MAX = 256;
    int V_MIN = 0;
    int V_MAX = 256;
    const int MIN_OBJECT_AREA = 40*40;

    ColorKeyer::ColorKeyer() : numberOfMusicChips(0) {

        numberOfMusicChips = 3;
        //musicChips.resize(numberOfMusicChips);
        MusicChip chip1(MusicChip::SQUARE, 0);
        MusicChip chip2(MusicChip::SQUARE, 0);
        MusicChip chip3(MusicChip::SQUARE, 0);
        MusicChip chip4(MusicChip::HEXAGON, 0);

        //werte setzen
        chip1.setHSVmin( Scalar(14, 130, 0) ); //gelb
        chip1.setHSVmax( Scalar(32, 255, 255) );
        chip2.setHSVmin( Scalar(109, 60, 0) ); //blau(lila)
        chip2.setHSVmax( Scalar(130, 255, 255) );
        chip3.setHSVmin( Scalar(40, 20, 0) ); // gruen
        chip3.setHSVmax( Scalar(75, 255, 255) );
        chip4.setHSVmin( Scalar(109, 60, 0) ); //blau(lila)
        chip4.setHSVmax( Scalar(130, 255, 255) );

        //musicchips hinzufuegen
        musicChips.push_back(chip1);
        musicChips.push_back(chip2);
        musicChips.push_back(chip3);
        musicChips.push_back(chip4);

        //vector der result Matrizen initalisieren
        //outputs.resize(numberOfMusicChips);
        for(int i = 0; i < numberOfMusicChips; i++){
            outputs.push_back(Mat());
        }

        namedWindow("Control",WINDOW_AUTOSIZE);

        createTrackbar( "H_MIN", "Control", &H_MIN, H_MAX);
        createTrackbar( "H_MAX", "Control", &H_MAX, H_MAX);
        createTrackbar( "S_MIN", "Control", &S_MIN, S_MAX);
        createTrackbar( "S_MAX", "Control", &S_MAX, S_MAX);
        createTrackbar( "V_MIN", "Control", &V_MIN, V_MAX);
        createTrackbar( "V_MAX", "Control", &V_MAX, V_MAX);
    }



    Mat ColorKeyer::maskColor(const Mat &input, MusicChip musicChip){

        cvtColor(input, input, CV_BGR2HSV);
        Mat output(input.rows, input.cols, CV_8UC1);
        inRange(input, musicChip.getHSVmin(), musicChip.getHSVmax(), output);

        return output;
    }

    Mat ColorKeyer::maskShape(const Mat input, MusicChip &musicChip, int shape, double minSize){

        Mat output(input.rows, input.cols, CV_8UC1); // = Mat::zeros(input.size(), CV_8UC1);
        vector<Vec4i> hierachy;
        vector<vector<Point>> contures;

        findContours(input, contures, hierachy, RETR_LIST, CV_CHAIN_APPROX_TC89_KCOS);

        for(int i = 0; i < contures.size(); i++){
            vector<Point> approx;

            //prüfe ob konturen zu viereck passen
            approxPolyDP(contures[i], approx, 0.01*arcLength(contures[i], true), true);

            if(contourArea(contures[i]) >= minSize && approx.size() == shape){
                musicChip.setDetection(true);
                drawContours(output,contures,i,Scalar(255,255,255),CV_FILLED,8,noArray());
                break;
            } else musicChip.setDetection(false);
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
        Mat contourOutput;
		//Konturen finden
        findContours(temp, contours, hierarchy,  CV_RETR_LIST /*CV_RETR_CCOMP*/, CV_CHAIN_APPROX_NONE/*_SIMPLE*/ );

		bool objectFound = false;
        if (hierarchy.size() > 0) {

            int numMusiChips = hierarchy.size();
            if(numMusiChips < 2) {

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
        Mat result(input.rows, input.cols, CV_8UC1, Scalar(0,0,0));

        for(int i = 0; i < musicChips.size(); i++){
           //outputs[i] = maskColor(input, musicChips[i] );
           //Mat output(input.rows, input.cols, CV_8UC1);
           //outputs[i] = maskShape(outputs[i], musicChips[i], MusicChip::SQUARE , 50);

           //maskieren
           cvtColor(input, HSV, CV_BGR2HSV);
           //medianBlur(input,input,3);
           inRange(HSV, musicChips[i].getHSVmin(), musicChips[i].getHSVmax(), threshold);

           //filtern : opening und closing
           morphologyEx(threshold, threshold, MORPH_OPEN, element, Point(-1,-1), 2);
           morphologyEx(threshold, threshold, MORPH_CLOSE, element, Point(-1,-1), 2);



           //tracken
           trackMusicChip(i, musicChips[i], threshold, HSV, threshold /*input*/);

           result = result | threshold;
        }

        return result;//input; //
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

