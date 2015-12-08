#include "audioengine.h"
#include <QDebug>
AudioEngine::AudioEngine(int bufferSize)
    : bufferSize(bufferSize)
{
    qDebug() << __FUNCTION__;
    audioPlayer.setAudioSource(&audioFile);
}

void AudioEngine::open(const QString& sourceFileName){
    qDebug() << __FUNCTION__;
    audioFile.setFileName(sourceFileName);
}

void AudioEngine::start(){
    qDebug() << __FUNCTION__;
    audioPlayer.start();
}

void AudioEngine::stop(){
    qDebug() << __FUNCTION__;
    audioPlayer.stop();
}
void AudioEngine::setAudioProcessor(AudioProcessor *audioProcessor){
    qDebug() << __FUNCTION__;
    audioPlayer.setAudioProcessor(audioProcessor);
}
