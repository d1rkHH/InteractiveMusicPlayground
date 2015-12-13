#include "soundcontrol.h"
#include "ui_soundcontrol.h"
#include "effectprocessor.h"
#include "musicchip.h"
#include <QDebug>

SoundControl::SoundControl(QWidget *parent) :
    QObject(parent)
{
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    //processor = new EffectProcessor();

    redPlayer = new AudioPlayer(this);
    redTrack = new AudioFile();
    redPlayer->setObjectName("RED");
    redPlayer->setAudioSource(redTrack);
    //redPlayer->setAudioProcessor(processor);
    yellowPlayer = new AudioPlayer(this);
    yellowTrack = new AudioFile();
    yellowPlayer->setObjectName("YELLOW");
    yellowPlayer->setAudioSource(yellowTrack);
    //yellowPlayer->setAudioProcessor(processor);

    greenPlayer = new AudioPlayer(this);
    greenTrack = new AudioFile();
    greenPlayer->setObjectName("GREEN");
    greenPlayer->setAudioSource(greenTrack);
    //greenPlayer->setAudioProcessor(processor);

    bluePlayer = new AudioPlayer(this);
    blueTrack = new AudioFile();
    bluePlayer->setObjectName("BLUE");
    bluePlayer->setAudioSource(blueTrack);
    //bluePlayer->setAudioProcessor(processor);

    purplePlayer = new AudioPlayer(this);
    purpleTrack = new AudioFile();
    purplePlayer->setObjectName("PURPLE");
    purplePlayer->setAudioSource(purpleTrack);
    //purplePlayer->setAudioProcessor(processor);
}

SoundControl::~SoundControl()
{
   qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
   delete redPlayer;
   delete greenPlayer;
   delete bluePlayer;
   delete yellowPlayer;
   delete purplePlayer;
   delete redTrack;
   delete greenTrack;
   delete yellowTrack;
   delete blueTrack;
   delete purpleTrack;
   delete processor;
}

void SoundControl::play(Point position){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    MusicChip* sender = qobject_cast<MusicChip*>(QObject::sender());
    AudioPlayer* player = getPlayer(sender->getRange().getName());
    if(player == 0){
        qDebug() << "Invalid Color - no corresponding audioPlayer";
        return;
    }
    player->start();

}

AudioPlayer* SoundControl::getPlayer(QString playerName){
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

AudioFile* SoundControl::getTrack(QString playerName){
    if(playerName == redPlayer->objectName()){
        return redTrack;
    } else if (playerName == yellowPlayer->objectName()){
        return yellowTrack;
    } else if (playerName == greenPlayer->objectName()){
        return greenTrack;
    } else if (playerName == bluePlayer->objectName()){
        return blueTrack;
    } else if (playerName == purplePlayer->objectName()){
        return purpleTrack;
    } else {
        return 0;
    }
}

void SoundControl::stop(){
     qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
     MusicChip* sender = qobject_cast<MusicChip*>(QObject::sender());
     AudioPlayer* player = getPlayer(sender->getRange().getName());
     if(player == 0){
         qDebug() << "Invalid Color - no corresponding audioPlayer";
         return;
     }
     player->stop();
}

void SoundControl::applyEffects(Point position){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
}

void SoundControl::setTrack(QString track){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    MusicChip* sender = qobject_cast<MusicChip*>(QObject::sender());
    AudioFile* file = getTrack(sender->getRange().getName());
    if(file == 0){
        qDebug() << "Invalid Color - no corresponding audioFile";
        return;
    }
    file->setFileName(track);
}

void SoundControl::setEffects(Point e1, Point e2, Point e3, Point e4){
   qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
}

