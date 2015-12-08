#include "musicchip.h"
#include <QDebug>

ColorRange MusicChip::YELLOW = ColorRange(Scalar(14,130,0), Scalar(32,255,255));
ColorRange MusicChip::GREEN = ColorRange(Scalar(40,20,0), Scalar(75,255,255));
ColorRange MusicChip::RED = ColorRange(Scalar(0,50,0), Scalar(15,255,255));
ColorRange MusicChip::BLUE = ColorRange(Scalar(95,50,0), Scalar(105,255,255));
ColorRange MusicChip::PURPLE = ColorRange(Scalar(109,60,0), Scalar(130,255,255));

MusicChip::MusicChip(int contures, ColorRange &range, QString track):detected(false){
    qDebug() << __FUNCTION__;
    this->contures = contures;
    this->range = &range;
    this->file = new AudioFile(1024);
    file->setFileName(track);
    this->audioPlayer = new AudioPlayer(999);
    qDebug() << "File null? " <<(file == 0);
    this->audioPlayer->setAudioSource(file);
}

MusicChip::MusicChip():detected(false){
    qDebug() << __FUNCTION__;
    this->audioPlayer = new AudioPlayer(999);
}

MusicChip::~MusicChip(void){
    qDebug() << __FUNCTION__;
}

void MusicChip::playTrack(){
    //effectProcessor->setChipCenter(center);
    if(!detected){
        qDebug() << __FUNCTION__ << "Detected false";
        detected = true;
        audioPlayer->start();
    } else {
        qDebug() << __FUNCTION__ << "Detected true";
    }
}

void MusicChip::setEffectProcessor(EffectProcessor* processor){
    qDebug() << __FUNCTION__;
    /*this->effectProcessor = processor;
    audioPlayer->setAudioProcessor(effectProcessor);*/
    this->effectProcessor = 0;
    audioPlayer->setAudioProcessor(0);
}


void MusicChip::setCenter(int x, int y){
    qDebug() << __FUNCTION__;
    this->center = cv::Point(x,y);
}

int MusicChip::getConture(){
    qDebug() << __FUNCTION__;
	return contures;
}

void MusicChip::setDetected(bool isDetected){
    qDebug() << __FUNCTION__;
    this->detected = isDetected;
}

Point MusicChip::getCenter(){
    qDebug() << __FUNCTION__;
    return this->center;
}

ColorRange MusicChip::getRange(){
    qDebug() << __FUNCTION__;
    return *range;
}
