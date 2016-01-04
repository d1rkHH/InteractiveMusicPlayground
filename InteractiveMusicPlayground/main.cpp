#include "videoplayer.h"
#include "soundcontrol.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    qRegisterMetaType<Point>("Point");
    SoundControl* soundControl = new SoundControl();
    VideoPlayer w(soundControl);
    w.show();

    return a.exec();
}
