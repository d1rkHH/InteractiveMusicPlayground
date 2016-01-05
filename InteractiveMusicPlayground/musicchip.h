#ifndef MUSICCHIP
#define MUSICCHIP

#include <opencv2/opencv.hpp>
#include <QObject>
#include "colorrange.h"
#include "shapes.h"

using namespace cv;

class MusicChip : public QObject{

    Q_OBJECT

public:
    MusicChip(int contour, ColorRange &range, QString fileName, QObject* parent = 0);
    ~MusicChip(void);
    void handleAudio(bool detected, Point position = Point(0,0), int positionTolerance = 5);
    void sendTrack();
    //Getter and Setter
    ColorRange getRange();
    int getContour();
    QString getFileName();
    Point getCenter();
    void setCenter(int x, int y);
    void setCenter(Point center);

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

    bool hasPositionChanged(int tolerance, Point position);
};

#endif // MUSICCHIP

