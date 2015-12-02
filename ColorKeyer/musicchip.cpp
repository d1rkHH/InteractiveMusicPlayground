#include "musicchip.h"

MusicChip::MusicChip(Scalar color, int contures, QString track){
    this->color = color;
    this->contures = contures;
    this->track = track;
}

void MusicChip::setCenter(int x, int y){
    this->center = cv::Point(x,y);
}
