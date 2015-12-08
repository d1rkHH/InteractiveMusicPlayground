#include "musicchip.h"
#include <QDebug>

ColorRange MusicChip::YELLOW = ColorRange(Scalar(14,130,0), Scalar(32,255,255));
ColorRange MusicChip::GREEN = ColorRange(Scalar(40,20,0), Scalar(75,255,255));
ColorRange MusicChip::RED = ColorRange(Scalar(0,50,0), Scalar(15,255,255));
ColorRange MusicChip::BLUE = ColorRange(Scalar(95,50,0), Scalar(105,255,255));
ColorRange MusicChip::PURPLE = ColorRange(Scalar(109,60,0), Scalar(130,255,255));


MusicChip::MusicChip(int contures, QString track):detected(false){
      //qDebug() << " " << track;
    //this->contures = contures;
    //this->file = new AudioFile(1024);
    //file->setFileName(track);
    //this->audioPlayer->setAudioSource(&file);
    //this->audioPlayer = new AudioPlayer(999);
}

MusicChip::MusicChip(int contures, ColorRange &range, QString track):detected(false){
    this->contures = contures;
    this->range = &range;
    this->file = new AudioFile(1024);
    file->setFileName(track);
    this->audioPlayer = new AudioPlayer(999);
    qDebug() << (file == 0);
    this->audioPlayer->setAudioSource(file);
}

MusicChip::MusicChip():detected(false){
    this->audioPlayer = new AudioPlayer(999);
}

MusicChip::~MusicChip(void){
}

void MusicChip::playTrack(){
    effectProcessor->setChipCenter(center);
    if(!detected){
        detected = true;
        audioPlayer->start();
    }
}

void MusicChip::setEffectProcessor(EffectProcessor* processor){
    this->effectProcessor = processor;
    audioPlayer->setAudioProcessor(effectProcessor);
}


void MusicChip::setCenter(int x, int y){
    this->center = cv::Point(x,y);
}

int MusicChip::getConture(){
	return contures;
}

void MusicChip::setDetected(bool isDetected){
    this->detected = isDetected;
}

Point MusicChip::getCenter(){
    return this->center;
}

ColorRange MusicChip::getRange(){
    return *range;
}
