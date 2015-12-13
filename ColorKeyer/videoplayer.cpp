#include <QFileDialog>
#include "videoplayer.h"
#include "ui_videoplayer.h"
#include "musicchip.h"
#include "colorrange.h"
#include "effectprocessor.h"
#include "audioplayer.h"
#include "audiofile.h"
#include "audioprocessor.h"

VideoPlayer::VideoPlayer(SoundControl *soundControl, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VideoPlayer)
    , videoThread(new VideoEngine)
    , colorKeyer(new ColorKeyer(soundControl))
{
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    ui->setupUi(this);
    videoThread->setProcessor(colorKeyer);
    connect(videoThread, SIGNAL(sendInputImage(const QImage&)), ui->inputFrame, SLOT(setImage(const QImage&)));
    connect(videoThread, SIGNAL(sendProcessedImage(const QImage&)), ui->processedFrame , SLOT(setImage(const QImage&)));
}

VideoPlayer::~VideoPlayer()
{
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    delete videoThread;
    delete colorKeyer;
    delete ui;
}

void VideoPlayer::on_playButton_clicked()
{
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    videoThread->start();
}


void VideoPlayer::on_openVideoFileButton_clicked()
{
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    // Kamera
    videoThread->openCamera();
    videoThread->start();
    return;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());

    if (!fileName.isEmpty()) {
        videoThread->openFile(fileName);
     }

}

void VideoPlayer::on_colorComboBox_currentIndexChanged(const QString &color)
{
    this->color = color;
    if(this->color == "RED"){
        preLoadScrollBars(ColorRange::RED);
    } else if(this->color == "YELLOW"){
        preLoadScrollBars(ColorRange::YELLOW);
    } else if(this->color == "GREEN"){
        preLoadScrollBars(ColorRange::GREEN);
    } else if(this->color == "BLUE"){
        preLoadScrollBars(ColorRange::BLUE);
    } else if(this->color == "PURPLE"){
        preLoadScrollBars(ColorRange::PURPLE);
    }
}

void VideoPlayer::preLoadScrollBars(ColorRange range){
    ui->minHueScrollbar->setValue(range.min[0]);
    ui->minSatScrollbar->setValue(range.min[1]);
    ui->minValScrollbar->setValue(range.min[2]);
    ui->maxHueScrollbar->setValue(range.max[0]);
    ui->maxSatScrollbar->setValue(range.max[1]);
    ui->maxValScrollbar->setValue(range.max[2]);
}

void VideoPlayer::setValueForColor(ColorRange::RangeIndex index, int value){
    if(this->color == "RED"){
       ColorRange::RED.setValue(index,value);
    } else if(this->color == "YELLOW"){
        ColorRange::YELLOW.setValue(index,value);
    } else if(this->color == "GREEN"){
        ColorRange::GREEN.setValue(index,value);
    } else if(this->color == "BLUE"){
        ColorRange::BLUE.setValue(index,value);
    } else if(this->color == "PURPLE"){
        ColorRange::PURPLE.setValue(index,value);
    }
}

void VideoPlayer::on_minHueScrollbar_valueChanged(int value)
{
    setValueForColor(ColorRange::MIN_HUE, value);
    ui->minhue->setText(QString::number(value));
}

void VideoPlayer::on_minSatScrollbar_valueChanged(int value)
{
    setValueForColor(ColorRange::MIN_SAT, value);
    ui->minsat->setText(QString::number(value));
}

void VideoPlayer::on_minValScrollbar_valueChanged(int value)
{
    setValueForColor(ColorRange::MIN_VAL, value);
    ui->minval->setText(QString::number(value));
}

void VideoPlayer::on_maxHueScrollbar_valueChanged(int value)
{
    setValueForColor(ColorRange::MAX_HUE, value);
    ui->maxhue->setText(QString::number(value));
}

void VideoPlayer::on_maxSatScrollbar_valueChanged(int value)
{
    setValueForColor(ColorRange::MAX_SAT, value);
    ui->maxsat->setText(QString::number(value));
}

void VideoPlayer::on_maxValScrollbar_valueChanged(int value)
{
    setValueForColor(ColorRange::MAX_VAL, value);
    ui->maxval->setText(QString::number(value));
}

void VideoPlayer::on_medianBlurScrollbar_valueChanged(int value)
{
    int newvalue = 0;
    if(value < 2){
        colorKeyer->setMedianBlurValue(0);
    } else if(value % 2 == 0){
        newvalue = value + 1;
        colorKeyer->setMedianBlurValue(value + 1);
        ui->medianBlurScrollbar->setValue(value+1);
    } else {
        newvalue = value;
        colorKeyer->setMedianBlurValue(value);
        ui->medianBlurScrollbar->setValue(value);
    }
    ui->medianblur->setText(QString::number(newvalue));
}

void VideoPlayer::on_openingScrollbar_valueChanged(int value)
{
    colorKeyer->setOpenValue(value);
    ui->opening->setText(QString::number(value));
}

void VideoPlayer::on_closingScrollbar_valueChanged(int value)
{
    colorKeyer->setCloseValue(value);
    ui->closing->setText(QString::number(value));
}

void VideoPlayer::on_minChipSizeScrollbar_valueChanged(int value)
{
    colorKeyer->setMinChipSize(value);
    ui->minchipsize->setText(QString::number(value));
}
