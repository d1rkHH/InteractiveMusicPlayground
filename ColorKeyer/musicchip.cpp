#include "musicchip.h"

ColorRange MusicChip::YELLOW = ColorRange(Scalar(14,130,0), Scalar(32,255,255));
ColorRange MusicChip::GREEN = ColorRange(Scalar(40,20,0), Scalar(75,255,255));
ColorRange MusicChip::RED = ColorRange(Scalar(0,50,0), Scalar(15,255,255));
ColorRange MusicChip::BLUE = ColorRange(Scalar(95,50,0), Scalar(105,255,255));
ColorRange MusicChip::PURPLE = ColorRange(Scalar(109,60,0), Scalar(130,255,255));


MusicChip::MusicChip(int contures, QString track){
    this->contures = contures;
    this->track = track;
}

MusicChip::MusicChip(int contures, ColorRange &range, QString track){
    this->contures = contures;
    this->range = &range;
    this->track = track;
}

MusicChip::MusicChip(){

}

MusicChip::~MusicChip(void){
}


void MusicChip::setCenter(int x, int y){
    this->center = cv::Point(x,y);
}

void MusicChip::setDetection(bool detec){
    this->detection = detec;
}

int MusicChip::getConture(){
	return contures;
}

Point MusicChip::getCenter(){
    return this->center;
}

bool MusicChip::isDetected(){
    return this->detection;
}

ColorRange MusicChip::getRange(){
    return *range;
}
