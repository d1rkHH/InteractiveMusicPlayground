#include "videoplayer.h"

VideoPlayer::VideoPlayer(SoundControl *soundControl, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VideoPlayer)
    , videoThread(new VideoEngine)
    , imageprocessor(new ImageProcessor(soundControl))
{
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    ui->setupUi(this);
    videoThread->setProcessor(imageprocessor);
    connect(videoThread, SIGNAL(sendInputImage(const QImage&)), ui->inputFrame, SLOT(setImage(const QImage&)));
    connect(videoThread, SIGNAL(sendProcessedImage(const QImage&)), ui->processedFrame , SLOT(setImage(const QImage&)));
}

VideoPlayer::~VideoPlayer() {
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    delete videoThread;
    delete imageprocessor;
    delete ui;
}

void VideoPlayer::on_openVideoFileButton_clicked() {
    qDebug() << "Thread: " << this->thread() << " " << __FUNCTION__;
    // Kamera
    videoThread->openCamera();
    videoThread->start();
}

void VideoPlayer::on_colorComboBox_currentIndexChanged(const QString &color) {
    this->color = color;
    if(this->color == ColorRange::RED.getName()){
        preLoadScrollBars(ColorRange::RED);
    } else if(this->color == ColorRange::YELLOW.getName()){
        preLoadScrollBars(ColorRange::YELLOW);
    } else if(this->color == ColorRange::GREEN.getName()){
        preLoadScrollBars(ColorRange::GREEN);
    } else if(this->color == ColorRange::BLUE.getName()){
        preLoadScrollBars(ColorRange::BLUE);
    } else if(this->color == ColorRange::PURPLE.getName()){
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
    if(this->color == ColorRange::RED.getName()){
       ColorRange::RED.setValue(index,value);
    } else if(this->color == ColorRange::YELLOW.getName()){
        ColorRange::YELLOW.setValue(index,value);
    } else if(this->color == ColorRange::GREEN.getName()){
        ColorRange::GREEN.setValue(index,value);
    } else if(this->color == ColorRange::BLUE.getName()){
        ColorRange::BLUE.setValue(index,value);
    } else if(this->color == ColorRange::PURPLE.getName()){
        ColorRange::PURPLE.setValue(index,value);
    }
}

void VideoPlayer::on_minHueScrollbar_valueChanged(int value) {
    setValueForColor(ColorRange::MIN_HUE, value);
    ui->minhue->setText(QString::number(value));
}

void VideoPlayer::on_minSatScrollbar_valueChanged(int value) {
    setValueForColor(ColorRange::MIN_SAT, value);
    ui->minsat->setText(QString::number(value));
}

void VideoPlayer::on_minValScrollbar_valueChanged(int value) {
    setValueForColor(ColorRange::MIN_VAL, value);
    ui->minval->setText(QString::number(value));
}

void VideoPlayer::on_maxHueScrollbar_valueChanged(int value) {
    setValueForColor(ColorRange::MAX_HUE, value);
    ui->maxhue->setText(QString::number(value));
}

void VideoPlayer::on_maxSatScrollbar_valueChanged(int value) {
    setValueForColor(ColorRange::MAX_SAT, value);
    ui->maxsat->setText(QString::number(value));
}

void VideoPlayer::on_maxValScrollbar_valueChanged(int value) {
    setValueForColor(ColorRange::MAX_VAL, value);
    ui->maxval->setText(QString::number(value));
}

//Set the MedianBlur in imageprocessor. This method only allows values
//accepted by the medianBlur method from OpenCV
void VideoPlayer::on_medianBlurScrollbar_valueChanged(int value) {
    int newvalue = 0;
    if(value < 2){
        imageprocessor->setMedianBlurValue(0);
    } else if(value % 2 == 0){
        newvalue = value + 1;
        imageprocessor->setMedianBlurValue(value + 1);
        ui->medianBlurScrollbar->setValue(value+1);
    } else {
        newvalue = value;
        imageprocessor->setMedianBlurValue(value);
        ui->medianBlurScrollbar->setValue(value);
    }
    ui->medianblur->setText(QString::number(newvalue));
}

void VideoPlayer::on_openingScrollbar_valueChanged(int value) {
    imageprocessor->setOpenValue(value);
    ui->opening->setText(QString::number(value));
}

void VideoPlayer::on_closingScrollbar_valueChanged(int value) {
    imageprocessor->setCloseValue(value);
    ui->closing->setText(QString::number(value));
}

void VideoPlayer::on_minChipSizeScrollbar_valueChanged(int value) {
    imageprocessor->setMinChipSize(value);
    ui->minchipsize->setText(QString::number(value));
}
