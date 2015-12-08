#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMainWindow>
#include <QImage>
#include "videoengine.h"
#include "colorkeyer.h"
namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ColorKeyer* colorKeyer;
    ~VideoPlayer();
    void playAudio();

private slots:
    void on_playButton_clicked();
    void on_openVideoFileButton_clicked();
    void on_colorComboBox_currentIndexChanged(const QString &color);

    void on_minHueScrollbar_valueChanged(int value);

    void on_minSatScrollbar_valueChanged(int value);

    void on_minValScrollbar_valueChanged(int value);

    void on_maxHueScrollbar_valueChanged(int value);

    void on_maxSatScrollbar_valueChanged(int value);

    void on_maxValScrollbar_valueChanged(int value);

    void on_medianBlurScrollbar_valueChanged(int value);

    void on_openingScrollbar_valueChanged(int value);

    void on_closingScrollbar_valueChanged(int value);

private:
    Ui::VideoPlayer *ui;
    VideoEngine *videoThread;
    QString color;
    void setValueForColor(ColorRange::RangeIndex index, int value);
    void preLoadScrollBars(ColorRange range);

};

#endif // VIDEOPLAYER_H
