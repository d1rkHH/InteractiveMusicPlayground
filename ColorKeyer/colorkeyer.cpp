#include "colorkeyer.h"

using namespace cv;

// Referenzfarbe
// ACHTUNG, die Reihenfolge ist BGR!
// ToDo: dies von aussen einstellbar machen
const Vec3b REFERENCE_COLOR(54, 39, 97);	// BGR

// Schwellwert
// ToDo: dies von aussen einstellbar machen
const int THRESHOLD = 16;

ColorKeyer::ColorKeyer()
{
}

void ColorKeyer::startProcessing(const VideoFormat& format){
    // Höhe: format.frameHeight()
    // Breite: format.frameWidth()
    // Framerate: format.framesPerSecond()
    // Pixelart: format.type() (CV_8UC1=Graustufen, CV_8UC3=BGR)
}

Mat ColorKeyer::maskColor(const Mat &input){
    // leeres Graustufenbild erzeugen, alle Pixel schwarz
    // input.rows = Anzahl Zeilen = Höhe
    // input.cols = Anzahl Spalten = Breite
    // Typ CV_8UC1 = Graustufenbild
    Mat output(input.rows, input.cols, CV_8UC1);


    for(int x = 0; x < input.cols; x++){
        for(int y = 0; y < input.rows; y++){
            // Holt Pixel an Position x, y
            Vec3b inputPixel = input.at<Vec3b>(y,x);

            // Abstand zur Referenzfarbe im RGB-Farbraum
            double distance = norm(inputPixel, REFERENCE_COLOR);

            // Schwellwertbildung:
            // weisse Pixel: die gesuchte Farbe
            // schwarze Pixel: unerwünschte Farbe
            uchar outputPixel = 0;
            if (distance < THRESHOLD){
                outputPixel = 255;
            }

            // Ausgabepixel setzen
            output.at<uchar>(y,x) = outputPixel;
        }
    }
    return output;
}
Mat ColorKeyer::process(const Mat &input){
    Mat output = maskColor(input);
//    medianBlur(output,output, 5);
    erode(output, output, Mat());
    dilate(output, output, Mat());

    Point center = centerOfMass(output);
    qDebug() << center.x << " " << center.y;
    return output;
}

Point ColorKeyer::centerOfMass(Mat& image){
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
