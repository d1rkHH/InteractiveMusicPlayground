#include "audioengine.h"

AudioEngine::AudioEngine(int bufferSize)
    : bufferSize(bufferSize)
{
    audioPlayer.setAudioSource(&audioFile);
}

void AudioEngine::open(const QString& sourceFileName){
    audioFile.setFileName(sourceFileName);
}

void AudioEngine::start(){
    audioPlayer.start();
}

void AudioEngine::stop(){
    audioPlayer.stop();
}
void AudioEngine::setAudioProcessor(AudioProcessor *audioProcessor){
    audioPlayer.setAudioProcessor(audioProcessor);
}
