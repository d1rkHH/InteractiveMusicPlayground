#include "videoplayer.h"
#include "soundcontrol.h"
#include "audioplayer.h"
#include "effectprocessor.h"
#include <QApplication>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Point>("Point");
    SoundControl* soundControl = new SoundControl();
    VideoPlayer w(soundControl);
    w.show();

    return a.exec();
}
