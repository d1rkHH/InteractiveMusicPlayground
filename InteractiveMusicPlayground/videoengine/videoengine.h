#ifndef VIDEOENGINE_H
#define VIDEOENGINE_H

#include <QThread>
#include <QImage>
#include <QMutex>
#include "videoprocessor.h"
#include "cvmattoqimage.h"
#include "videoformat.h"


class VideoEngine : public QThread
{
    Q_OBJECT
public:
    VideoEngine();
    ~VideoEngine();
    void openFile(const QString& file);
    void openCamera(int device = 0, int channel = 0);
    void setProcessor(VideoProcessor*);
    VideoProcessor* getVideoProcessor();
    const VideoFormat& videoFormat() const;
    int framePosition();
    void setDisableVideoOutput(bool value);
protected:
    void run();
public slots:
    void stop();
signals:
    void sendInputImage(const QImage&);
    void sendProcessedImage(const QImage&);
private:
    cv::VideoCapture videoCapture;
    VideoFormat _videoFormat;
    bool stopped;
    QMutex mutex;
    VideoProcessor* processor;
    bool usingCamera;
    int cameraChannel;
    bool disableVideoOutput;
};


#endif // VIDEOENGINE_H
