#pragma once
#include <QtWidgets/QMainWindow>
#include <qtimer.h>
#include <qimage.h>
#include <qelapsedtimer.h>
#include <qobject.h>
#include <qmainwindow.h>
#include <qthreadpool.h>
#include <qprogressbar.h>
#include <qthread.h>
#include <qdebug.h>
#include <string>
#include <qfiledialog.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <qslider.h>
#include <qpushbutton.h>

#include <QtWidgets/QMainWindow>
#include "VideoPlayerSetting.h"
#include "VedioPlayerProcessing.h"
#include "ui_VideoPlayerMainWindow.h"

#include <opencv2/opencv.hpp>
#include <core.hpp>
#include <highgui.hpp>
namespace Ui {
    class VideoPlayerMianWindow;
}



class VideoPlayerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    VideoPlayerMainWindow(QWidget *parent = Q_NULLPTR);

    ~VideoPlayerMainWindow();
    VideoPlayerSetting* player = NULL;

private:
    Ui::VideoPlayerMainWindowClass ui;

    VedioPlayerProcessing* frame_hanle_from = NULL;
    QString file_name;

private slots:
    void Open_video_Slot();
    void Frame_handle_Slot();
    void start_btn_Slot();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_slider_sliderMoved(int position);
    void on_slider_sliderPressed();
    //void on_choose_btn_clicked();
    void vedioProcessing();

};
