#include "soundcontrol.h"
#include <iostream>

SoundControl::SoundControl(QWidget *parent)
    : QObject(parent)
    , started(false){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
}

SoundControl::~SoundControl() {
   qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
   for(uint i = 0; i < musicChipPlayers.size(); i++){
       delete musicChipPlayers[i];
   }
}

//Start audioPlayers (called when camera input is started
void SoundControl::start(){
    std::cout << "start sound control" << std::endl;
    if(!started){
        started = true;
        for(uint i = 0; i < musicChipPlayers.size(); i++){
            std::cout << "start player" << i << endl;
            musicChipPlayers[i]->getAudioPlayer()->start();
        }
    }
}

void SoundControl::play(Point position){
    MusicChip* sender = qobject_cast<MusicChip*>(QObject::sender());
    MusicChipPlayer* player = getPlayer(sender->objectName());
    player->getEffectProcessor()->active();
    player->getEffectProcessor()->setChipCenter(position);
}

void SoundControl::stop(){
    MusicChip* sender = qobject_cast<MusicChip*>(QObject::sender());
    MusicChipPlayer* player = getPlayer(sender->objectName());
    player->getEffectProcessor()->off();
}

MusicChipPlayer* SoundControl::getPlayer(QString playerName){
    for(uint i = 0; i < musicChipPlayers.size(); i++){
        if(playerName == musicChipPlayers[i]->objectName()){
            return musicChipPlayers[i];
        }
    }
    qDebug() << "No player found!";
    return 0;
}

void SoundControl::applyEffects(Point position){
    MusicChip* sender = qobject_cast<MusicChip*>(QObject::sender());
    MusicChipPlayer* player = getPlayer(sender->objectName());
    player->getEffectProcessor()->setChipCenter(position);
}

void SoundControl::setTrack(){
    MusicChip* sender = qobject_cast<MusicChip*>(QObject::sender());
    MusicChipPlayer* player = new MusicChipPlayer(sender->objectName(), this);
    musicChipPlayers.reserve(1);
    musicChipPlayers.push_back(player);
    player->getAudioFile()->setFileName(sender->getFileName());
}

void SoundControl::setEffects(Point e1, Point e2, Point e3, Point e4){
   for(uint i = 0; i < musicChipPlayers.size(); i++){
        EffectProcessor* e = musicChipPlayers[i]->getEffectProcessor();
        e->setEffectPositions(e1, e2, e3, e4);
   }
}

