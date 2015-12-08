#include <QFileDialog>
#include "videoplayer.h"
#include "ui_videoplayer.h"
#include "musicchip.h"
#include "colorrange.h"

VideoPlayer::VideoPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VideoPlayer)
    , videoThread(new VideoEngine)
    , colorKeyer(new ColorKeyer())
{
    ui->setupUi(this);
    videoThread->setProcessor(colorKeyer);
    connect(videoThread, SIGNAL(sendInputImage(const QImage&)), ui->inputFrame, SLOT(setImage(const QImage&)));
    connect(videoThread, SIGNAL(sendProcessedImage(const QImage&)), ui->processedFrame , SLOT(setImage(const QImage&)));

}

VideoPlayer::~VideoPlayer()
{
    delete videoThread;
    delete colorKeyer;
    delete ui;
}


void VideoPlayer::on_playButton_clicked()
{
    videoThread->start();
}


void VideoPlayer::on_openVideoFileButton_clicked()
{
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
        preLoadScrollBars(MusicChip::RED);
    } else if(this->color == "YELLOW"){
        preLoadScrollBars(MusicChip::YELLOW);
    } else if(this->color == "GREEN"){
        preLoadScrollBars(MusicChip::GREEN);
    } else if(this->color == "BLUE"){
        preLoadScrollBars(MusicChip::BLUE);
    } else if(this->color == "PURPLE"){
        preLoadScrollBars(MusicChip::PURPLE);
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
        MusicChip::RED.setValue(index,value);
    } else if(this->color == "YELLOW"){
        MusicChip::YELLOW.setValue(index,value);
    } else if(this->color == "GREEN"){
        MusicChip::GREEN.setValue(index,value);
    } else if(this->color == "BLUE"){
        MusicChip::BLUE.setValue(index,value);
    } else if(this->color == "PURPLE"){
        MusicChip::PURPLE.setValue(index,value);
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
