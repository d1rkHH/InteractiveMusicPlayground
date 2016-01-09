#ifndef MUSICCHIP
#define MUSICCHIP

#include <opencv2/opencv.hpp>
#include <QObject>
#include "colorrange.h"
#include "shapes.h"
#include <QDebug>

using namespace cv;

//This class represents a physical object, the Music Chip. A music chip
//has to be of a certain color and has to have a certain geometric shape
//Also, every musicChip has its path to and audiofile, which will be played,
//is the musicChip detected by the camera
//The only method containing real logic is handleAudio, which calls the
//SoundControl based on the current status of the musicChip
class MusicChip : public QObject{

    Q_OBJECT

public:
    MusicChip(int contour, ColorRange &range, QString fileName, QObject* parent = 0);
    ~MusicChip();
    void handleAudio(bool detected, Point position = Point(0,0), int positionTolerance = 5);
    void sendTrack();
    //Getter and Setter
    ColorRange getRange();
    int getContour();
    QString getFileName();
    Point getCenter();
    void setCenter(int x, int y);
    void setCenter(Point center);
    void setLastDetected(Mat lastDetected, Point lastDetectedCenter);
    bool wasLastDetected(int tolerance);
    Mat getLastDetected();
    Point getLastDetectedCenter();

signals:
    //Signals to communicate with SoundControl
    //to handle the audio for this MusicChip
    void on(Point position);
    void off();
    void positionChanged(Point position);
    void passTrack();

private:
    //The ColorRange for this MusicChip
    ColorRange *range;
    //Number of contours for this MusicChip
    int contour;
    //Filename of the audiofile for this MusicChip
    QString fileName;
    //Is the audio for this MusicChip currently playing?
    bool playing;
    //The coordinates of the center of this music chip
    Point center;
    //The last time this musicChip was detected saved in a Mat
    Mat lastDetected;
    //Center of last Detected
    Point lastDetectedCenter;
    //Counter for when the last detected Mat is no longer viable
    int lastDetectedCounter;

    bool hasPositionChanged(int tolerance, Point position);
};

#endif // MUSICCHIP

