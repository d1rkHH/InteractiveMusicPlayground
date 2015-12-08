#include "videoplayer.h"
#include "audioplayer.h"
#include "effectprocessor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qDebug() << __FUNCTION__;
    QApplication a(argc, argv);
    VideoPlayer w;
    w.show();

    /*
    AudioPlayer audioPlayer(999);
    AudioFile file(1024);
    file.setFileName("C:\\Users\\Besitzer\\Programming\\cpp\\AVPRG\\InteractiveMusicPlayground\\demo.mp3");
    audioPlayer.setAudioSource(&file);
    //audioPlayer.setAudioProcessor(new EffectProcessor());
    audioPlayer.start();
    */

    return a.exec();
}
