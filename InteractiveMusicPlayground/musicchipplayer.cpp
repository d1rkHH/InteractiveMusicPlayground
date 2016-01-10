#include "musicchipplayer.h"

MusicChipPlayer::MusicChipPlayer(QString objectName, QObject *parent) : QObject(parent)
{
    this->setObjectName(objectName);
    this->player = new AudioPlayer(this);
    this->player->setAudioSource(new AudioFile());
    this->player->setAudioProcessor(new EffectProcessor());
}

MusicChipPlayer::~MusicChipPlayer(){
    delete player;
}

AudioPlayer* MusicChipPlayer::getAudioPlayer(){
    return this->player;
}

AudioFile* MusicChipPlayer::getAudioFile(){
    return static_cast<AudioFile*>(this->player->getAudioSource());
}

EffectProcessor* MusicChipPlayer::getEffectProcessor(){
    return static_cast<EffectProcessor*>(this->player->getAudioProcessor());
}
