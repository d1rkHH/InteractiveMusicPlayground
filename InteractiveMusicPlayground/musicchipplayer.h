#ifndef MUSICCHIPPLAYER_H
#define MUSICCHIPPLAYER_H

#include <QObject>
#include "audioplayer.h"
#include "audiofile.h"
#include "effectprocessor.h"

class MusicChipPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MusicChipPlayer(QString objectName, QObject *parent = 0);
    ~MusicChipPlayer();
    AudioPlayer* getAudioPlayer();
    AudioFile* getAudioFile();
    EffectProcessor* getEffectProcessor();
private:
    AudioPlayer* player;
    AudioFile* file;
    EffectProcessor* processor;
};

#endif // MUSICCHIPPLAYER_H
