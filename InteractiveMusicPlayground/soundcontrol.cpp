#include "soundcontrol.h"

SoundControl::SoundControl(QWidget *parent) :
    QObject(parent)
{
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    redPlayer = new MusicChipPlayer("RED", this);
    bluePlayer = new MusicChipPlayer("BLUE", this);
    greenPlayer = new MusicChipPlayer("GREEN", this);
    yellowPlayer = new MusicChipPlayer("YELLOW", this);
    purplePlayer = new MusicChipPlayer("PURPLE", this);
}

SoundControl::~SoundControl() {
   qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
   delete redPlayer;
   delete greenPlayer;
   delete bluePlayer;
   delete yellowPlayer;
   delete purplePlayer;
}

void SoundControl::play(Point position){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    MusicChip* sender = qobject_cast<MusicChip*>(QObject::sender());
    MusicChipPlayer* player = getPlayer(sender->getRange().getName());
    if(player == 0){
        qDebug() << "Invalid Color - no corresponding audioPlayer";
        return;
    }
    player->getEffectProcessor()->setVolume(1);

}


MusicChipPlayer* SoundControl::getPlayer(QString playerName){
    if(playerName == redPlayer->objectName()){
        return redPlayer;
    } else if (playerName == yellowPlayer->objectName()){
        return yellowPlayer;
    } else if (playerName == greenPlayer->objectName()){
        return greenPlayer;
    } else if (playerName == bluePlayer->objectName()){
        return bluePlayer;
    } else if (playerName == purplePlayer->objectName()){
        return purplePlayer;
    } else {
        return 0;
    }
}

void SoundControl::stop(){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    MusicChip* sender = qobject_cast<MusicChip*>(QObject::sender());
    MusicChipPlayer* player = getPlayer(sender->getRange().getName());
    if(player == 0){
        qDebug() << "Invalid Color - no corresponding audioPlayer";
        return;
    }
    player->getEffectProcessor()->setVolume(0);
}

void SoundControl::applyEffects(Point position){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
}

void SoundControl::setTrack(QString track){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    MusicChip* sender = qobject_cast<MusicChip*>(QObject::sender());
    MusicChipPlayer* player = getPlayer(sender->getRange().getName());
    if(player == 0){
        qDebug() << "Invalid Color - no corresponding audioPlayer";
        return;
    }
    player->getAudioFile()->setFileName(track);
    player->getAudioPlayer()->start();
}

void SoundControl::setEffects(Point e1, Point e2, Point e3, Point e4){
   qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
}

