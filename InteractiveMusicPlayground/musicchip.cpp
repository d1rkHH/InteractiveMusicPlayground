#include "musicchip.h"
#include <QDebug>

MusicChip::MusicChip(int contour, ColorRange &range, QString fileName,QObject* parent)
    :QObject(parent)
    , playing(false)
    , contour(contour)
    , range(&range)
    , fileName(fileName){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
}

MusicChip::~MusicChip(void){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
}

/* Pass this function true if the chip is currently detected and false if not
 * Also, pass the position if the chip got detected. It will get ignored if detected is false
 * If the corresponding audio track to this music chip is not playing and the chip is
 * not detected, just exit this function. If it is playing and is detected,
 * check if the position has changed and send a signal with the new position
*/
void MusicChip::handleAudio(bool detected, Point position, int positionTolerance){
    if(!detected && !playing){
        qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__ << "Not Detected and Not Playing";
        return;
    } else if(detected && playing && position != Point(0,0)){
        qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__ << "Detected and Playing";
        if(hasPositionChanged(positionTolerance, position)){
            emit positionChanged(position);
        }
    } else if (detected && !playing && position != Point(0,0)){
        //Chips got detected and the audio is not playing at the moment
        qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__ << "Detected and Not Playing";
        emit on(position);
        playing = true;
    } else if(!detected && playing){
        //Chip is no longer detected but still playing
        qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__ << "Not Detected and Playing";
        emit off();
        playing = false;
    }
}

//Wrapper-Method to emit passTrack from outside of MusicChip
void MusicChip::sendTrack(){
    emit passTrack(fileName);
}

/* Calculate if the position of the chip has changed. Pass a tolerance so
 * a few pixel difference won't result in unnecessary recalculation of effect strength
 *
*/
bool MusicChip::hasPositionChanged(int tolerance, Point position){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    return ((center.x + tolerance) < position.x || (center.x - tolerance) < position.x) && ((center.y + tolerance) < position.y || (center.y - tolerance) < position.y);
}

/*
 * Getters and Setters
 */

ColorRange MusicChip::getRange(){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    return *range;
}

int MusicChip::getContour(){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    return contour;
}

QString MusicChip::getFileName(){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    return fileName;
}

Point MusicChip::getCenter(){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    return this->center;
}

//Set center by two ints
void MusicChip::setCenter(int x, int y){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    this->center = cv::Point(x,y);
}

//Set center by Point
void MusicChip::setCenter(Point center){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    this->center = center;
}
