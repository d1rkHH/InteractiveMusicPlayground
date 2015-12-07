#include "musicchip.h"

MusicChip::MusicChip(int contures, QString track){
    this->contures = contures;
    this->track = track;
}

MusicChip::MusicChip(){

}

MusicChip::~MusicChip(void){
}


void MusicChip::setHSVmin(Scalar min){
    this->min = min;
}

void MusicChip::setHSVmax(Scalar max){
    this->max = max;
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
Scalar MusicChip::getHSVmin(){
    return min;
}

Scalar MusicChip::getHSVmax(){
    return max;
}

Point MusicChip::getCenter(){
    return this->center;
}

bool MusicChip::isDetected(){
    return this->detection;
}
