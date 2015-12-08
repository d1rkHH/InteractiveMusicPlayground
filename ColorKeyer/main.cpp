#include "videoplayer.h"
#include "audioplayer.h"
#include "effectprocessor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoPlayer w;
    w.show();

    return a.exec();
}
