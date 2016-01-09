#include "musicchip.h"

MusicChip::MusicChip(int contour, ColorRange &range, QString fileName,QObject* parent)
    :QObject(parent)
    , playing(false)
    , contour(contour)
    , range(&range)
    , fileName(fileName){
    //Set the Object name of this musicChip to the color plus the contour number
    this->setObjectName(this->range->getName() + contour);
}

MusicChip::~MusicChip(){
    delete range;
}

/* Pass this function true if the chip is currently detected and false if not
 * Also, pass the position if the chip got detected. It will get ignored if detected is false
 * If the corresponding audio track to this music chip is not playing and the chip is
 * not detected, just exit this function. If it is playing and is detected,
 * check if the position has changed and send a signal with the new position
*/
void MusicChip::handleAudio(bool detected, Point position, int positionTolerance){
    if(!detected && !playing){
        return;
    } else if(detected && playing && position != Point(0,0)){
        if(hasPositionChanged(positionTolerance, position)){
            emit positionChanged(position);
        }
    } else if (detected && !playing && position != Point(0,0)){
        //Chips got detected and the audio is not playing at the moment
        emit on(position);
        playing = true;
    } else if(!detected && playing){
        //Chip is no longer detected but still playing
        emit off();
        playing = false;
    }
}

//Wrapper-Method to emit passTrack from outside of MusicChip
void MusicChip::sendTrack(){
    emit passTrack();
}

/* Calculate if the position of the chip has changed. Pass a tolerance so
 * a few pixel difference won't result in unnecessary recalculation of effect strength
*/
bool MusicChip::hasPositionChanged(int tolerance, Point position){
    return ((center.x + tolerance) < position.x || (center.x - tolerance) < position.x) && ((center.y + tolerance) < position.y || (center.y - tolerance) < position.y);
}

//Calculates if the musicChip was detected some frames ago gated by tolerance parameter
bool MusicChip::wasLastDetected(int tolerance){
    lastDetectedCounter++;
    if(lastDetectedCounter-1 < tolerance){
        return true;
    }
    return false;
}

/*
 * Getters and Setters
 */

ColorRange MusicChip::getRange(){
    return *range;
}

int MusicChip::getContour(){
    return contour;
}

QString MusicChip::getFileName(){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    return fileName;
}

Point MusicChip::getCenter(){
    return this->center;
}

//Set center by two ints
void MusicChip::setCenter(int x, int y){
    this->center = cv::Point(x,y);
}

//Set center by Point
void MusicChip::setCenter(Point center){
    this->center = center;
}

//Set lastDetected. Also, refresh the counter for last detected
void MusicChip::setLastDetected(Mat lastDetected, Point lastDetectedCenter){
    this->lastDetected = lastDetected;
    this->lastDetectedCenter = lastDetectedCenter;
    this->lastDetectedCounter = 0;
}

Mat MusicChip::getLastDetected(){
    return this->lastDetected;
}

Point MusicChip::getLastDetectedCenter(){
    return this->lastDetectedCenter;
}
