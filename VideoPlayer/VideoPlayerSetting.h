#pragma once
#include <QThreadPool>
#include <QProgressBar>
#include <QThread>
#include <QDebug>
#include <string.h>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QSlider>
#include <opencv2/opencv.hpp>
#include "VedioPlayerProcessing.h"
#include <QLabel>
using namespace cv;

class VideoPlayerSetting : public QRunnable
{
public:
    VideoPlayerSetting(QSlider* slider, QLabel* video_label, QLabel* label_pos, QLabel* label_total);
    void play(QString path);
    void run();
    int Video_Slip(QString file_path);
    void Stop();
    void Start();
    int Faster();
    int Slower();
    void Pase();
    void PaseOrStart();
    void Set_postion(long po);
    double get_current_pos();
    static bool Is_Video_play;

private:
    QSlider* slider;
    QString Video_Path;
    QLabel* video_label;
    QLabel* label_pos;
    QLabel* label_total;
    VideoCapture capture;
    void show_img(Mat src, QLabel* label);
    Mat frame;
    bool Stop_Play = false;
    bool Is_Pase = false;
    int speed = 30;
    int pos = -1;
    VideoWriter videoRec;
};