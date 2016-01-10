#ifndef MUSICCHIPPLAYER_H
#define MUSICCHIPPLAYER_H

#include <QObject>
#include "audioplayer.h"
#include "audiofile.h"
#include "effectprocessor.h"

//This class is a wrapper for the AudioPlayer
//to handle the effectprocessor and audiofile
//easily
class MusicChipPlayer : public QObject
{
    Q_OBJECT
public:
    MusicChipPlayer(QString objectName, QObject *parent = 0);
    ~MusicChipPlayer();
    AudioPlayer* getAudioPlayer();
    AudioFile* getAudioFile();
    EffectProcessor* getEffectProcessor();
private:
    AudioPlayer* player;
};

#endif // MUSICCHIPPLAYER_H
