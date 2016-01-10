#include "AudioPlayer.h"
#include <QAudioOutput>
#include <QDebug>
#include <QFile>
// see class Generator in
// http://qt-project.org/doc/qt-4.8/multimedia-audiooutput-audiooutput-cpp.html

AudioPlayer::AudioPlayer(QObject* parent, int bufferSize)
    : QIODevice(parent)
    , audioSource(0)
    , audioBufferPos(0)
    , audioOutput(0)
    , numChannels(0)
    , bufferSize(bufferSize)
    , available(0)
    , audioProcessor(0)
    , endOfFile(false)
{
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
}
AudioPlayer::~AudioPlayer(){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    stop();
}
void AudioPlayer::setAudioSource(AudioSource* audioSource){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    this->audioSource = audioSource;
}
void AudioPlayer::setAudioProcessor(AudioProcessor*audioProcessor){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    this->audioProcessor = audioProcessor;
}

void AudioPlayer::stop(){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    close();
    if (audioSource){
        audioSource->stop();
    }
    audioOutput->stop();
    delete audioOutput;
    audioOutput = 0;
    audioFormat.setSampleType(QAudioFormat::Unknown);
    audioFormat.setChannelCount(0);
    audioFormat.setSampleRate(0);
    audioFormat.setSampleSize(0);
}

void AudioPlayer::start(){
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    close();
    if (audioSource != 0){
       audioSource->start();

       audioFormat.setCodec("audio/pcm");
       audioFormat.setByteOrder(QAudioFormat::LittleEndian);
       audioFormat.setChannelCount(audioSource->format().channelCount());
       audioFormat.setSampleRate(audioSource->format().sampleRate());
       audioFormat.setSampleSize(16);
       audioFormat.setSampleType(QAudioFormat::SignedInt);
       numChannels = audioSource->format().channelCount();
       inputChannelBuffer.resize(numChannels, bufferSize);
       outputChannelBuffer.resize(numChannels, bufferSize);
       if (audioProcessor != 0){
           audioProcessor->startProcessing(audioFormat);
       }
       QIODevice::open(QIODevice::ReadOnly);
       audioOutput = new QAudioOutput(audioFormat, this->parent());
       audioOutput->start(this);
   }
}


const QAudioFormat& AudioPlayer::format()const{
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    return audioFormat;
}



qint64 AudioPlayer::readData(char *data, qint64 bytesWanted) {
    if (audioSource == 0){
        return 0;
    }

    qint64 framesWanted = audioFormat.framesForBytes(bytesWanted);
    qint64 total = 0;
    while (framesWanted - total > 0) {
        if (available - audioBufferPos == 0){
            available = audioSource->read(inputChannelBuffer.buffer(), bufferSize);
            audioBufferPos = 0;
            if(audioProcessor != 0){
                audioProcessor->process(inputChannelBuffer.buffer(), outputChannelBuffer.buffer(), available);
            }
            else{
                inputChannelBuffer.copyTo(outputChannelBuffer, available);
            }
        }

        // convert float** to short
        const qint64 chunk = qMin<int>(available - audioBufferPos, framesWanted - total);
        outputChannelBuffer.toShort((short*)data, total, audioBufferPos, chunk);

        total += chunk;
        audioBufferPos += chunk ;
    }
    return audioFormat.bytesForFrames(total);
}

qint64 AudioPlayer::writeData(const char *data, qint64 len)
{
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

qint64 AudioPlayer::bytesAvailable()const{
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    return audioFormat.bytesForFrames(available - audioBufferPos);
}

AudioSource* AudioPlayer::getAudioSource(){
    return this->audioSource;
}

AudioProcessor* AudioPlayer::getAudioProcessor(){
    return this->audioProcessor;
}
