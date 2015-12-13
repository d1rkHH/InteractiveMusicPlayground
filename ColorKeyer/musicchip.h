#ifndef MUSICCHIP
#define MUSICCHIP

#include <opencv2/opencv.hpp>
#include "colorrange.h"
#include <QObject>
#include "shapes.h"

using namespace cv;

class MusicChip : public QObject{

    Q_OBJECT

public:
    MusicChip(int contour, ColorRange &range, QString fileName, QObject* parent = 0);
    ~MusicChip(void);
    void handleAudio(bool detected, Point position = Point(0,0), int positionTolerance = 5);
    void sendTrack(){emit passTrack(fileName);}
    //Getter and Setter
    ColorRange getRange();
    int getContour();
    QString getFileName();
    Point getCenter();
    void setCenter(int x, int y);
    void setCenter(Point center);

signals:
    void on(Point position);
    void off();
    void positionChanged(Point position);
    void passTrack(QString track);

private:
    ColorRange *range;
    int contour;
    QString fileName;
    bool playing;
    Point center;
    bool hasPositionChanged(int tolerance, Point position);
};

#endif // MUSICCHIP

