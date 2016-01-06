#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMainWindow>
#include <QImage>
#include "imageprocessor.h"
#include "videoengine.h"
#include "colorrange.h"
#include "ui_videoplayer.h"
#include "soundcontrol.h"
#include "colorrange.h"

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoPlayer(SoundControl* soundControl, QWidget *parent = 0);
    ImageProcessor* imageprocessor;
    ~VideoPlayer();

private slots:
    //Video Player
    void on_openVideoFileButton_clicked();
    //Color Control
    void on_colorComboBox_currentIndexChanged(const QString &color);
    void on_minHueScrollbar_valueChanged(int value);
    void on_minSatScrollbar_valueChanged(int value);
    void on_minValScrollbar_valueChanged(int value);
    void on_maxHueScrollbar_valueChanged(int value);
    void on_maxSatScrollbar_valueChanged(int value);
    void on_maxValScrollbar_valueChanged(int value);
    //Preprocessing Control
    void on_medianBlurScrollbar_valueChanged(int value);
    void on_openingScrollbar_valueChanged(int value);
    void on_closingScrollbar_valueChanged(int value);
    //Detection Control
    void on_minChipSizeScrollbar_valueChanged(int value);
    //Audio Control
    void on_playAudioButton_clicked();

private:
    Ui::VideoPlayer *ui;
    VideoEngine *videoThread;
    QString color;
    SoundControl* soundControl;
    void setValueForColor(ColorRange::RangeIndex index, int value);
    void preLoadScrollBars(ColorRange range);

};

#endif // VIDEOPLAYER_H
