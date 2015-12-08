#include "videoplayer.h"
#include "audioplayer.h"
#include "effectprocessor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoPlayer w;
    w.show();

    //Audio (TODO: External class)
    AudioPlayer audioPlayer(0,999);
    AudioFile file(1024);
    file.setFileName("C:\\Users\\Besitzer\\Programming\\cpp\\AVPRG\\InteractiveMusicPlayground\\demo.mp3");
    audioPlayer.setAudioSource(&file);
    audioPlayer.setAudioProcessor(&w.colorKeyer->effectProcessor);
    audioPlayer.start();

    return a.exec();
}
