#include "musicchipplayer.h"

MusicChipPlayer::MusicChipPlayer(QString objectName, QObject *parent) : QObject(parent)
{
    this->setObjectName(objectName);
    this->player = new AudioPlayer(this);
    this->file = new AudioFile();
    this->processor = new EffectProcessor(44100);
    this->player->setAudioSource(file);
    this->player->setAudioProcessor(processor);
}

MusicChipPlayer::~MusicChipPlayer(){
    delete player;
    delete file;
    delete processor;
}

AudioPlayer* MusicChipPlayer::getAudioPlayer(){
    return this->player;
}

AudioFile* MusicChipPlayer::getAudioFile(){
    return this->file;
}

EffectProcessor* MusicChipPlayer::getEffectProcessor(){
    return this->processor;
}
