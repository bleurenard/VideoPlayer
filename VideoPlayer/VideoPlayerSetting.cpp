#include "VideoPlayerSetting.h"
#include "opencv2/imgproc/types_c.h"
#include <iostream>
#include "Vibe.h"

using namespace std;

//初始化静态变量
bool VideoPlayerSetting::Is_Video_play = false;
VideoPlayerSetting::VideoPlayerSetting(QSlider* slider, QLabel* video_label, QLabel* label_pos, QLabel* label_total)
{
    //构造函数
    this->slider = slider;
    this->video_label = video_label;
    this->label_pos = label_pos;
    this->label_total = label_total;

}


void VideoPlayerSetting::show_img(Mat image, QLabel* label) {

    //    在label上显示opencv图片
    cv::cvtColor(image, image, CV_BGR2RGB);
    QImage img = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.cols * image.channels(), QImage::Format_RGB888).scaled(label->width(), label->height());

    label->clear();
    label->setPixmap(QPixmap::fromImage(img));
    //ui->processPushButton->setEnabled(true);

}
void VideoPlayerSetting::play(QString path) {
    Stop_Play = false;
    capture.open(path.toStdString());
    double FPS = capture.get(CAP_PROP_FPS);
    slider->setRange(0, capture.get(7));
    this->label_total->setText(QString::number(capture.get(7)));
    cv::waitKey(1000.0 / FPS);
    //      Is_Video_play==true;
    //      Stop_Play=false;
}
void VideoPlayerSetting::Stop() {
    //停止播放
    Stop_Play = true;
}
int VideoPlayerSetting::Faster() {
    if (speed > 5) {
        speed -= 5;
        return speed;
    }
    else {
        return 5;
    }


}
int VideoPlayerSetting::Slower() {
    if (speed < 1000) {
        speed += 20;

        return speed;
    }
    else {
        return 1000;
    }

}

void VideoPlayerSetting::Start() {
    //打开播放锁
    Stop_Play = false;
}
void VideoPlayerSetting::Pase() {
    //暂停

    Is_Pase = true;

}
void VideoPlayerSetting::PaseOrStart() {
    //暂停
    if (Is_Pase == true)
    {
        Is_Pase = false;
    }
    else {
        Is_Pase = true;
    }

}
double VideoPlayerSetting::get_current_pos() {
    return (capture.get(0));
}

void VideoPlayerSetting::Set_postion(long po) {
    //根据frame进行设置位置
    this->pos = po;
}
void VideoPlayerSetting::run() {
    //player的线程函数
    while (true) {
        //点击进度条响应 变化起始位置
        if (pos != -1) {
            capture.set(1, pos);
            pos = -1;
        }
        //暂停响应
        if (!Is_Pase) {
            bool ret = capture.read(frame);
            long i = capture.get(1);
            if (Stop_Play) {
                break;
            }
            if (!ret) {
                continue;
            }
            show_img(frame, video_label);
            QMetaObject::invokeMethod(slider, "setValue", Qt::QueuedConnection, Q_ARG(int, i));
            QMetaObject::invokeMethod(label_pos, "setText", Qt::QueuedConnection, Q_ARG(QString, QString::number(i)));
            /*QTest::qSleep(speed);*/
        }

    }
}

int VideoPlayerSetting::Video_Slip(QString file_name)
{
    Mat frame, gray, FGModel;
    Mat pre;
    VideoCapture capture;
    capture = VideoCapture(file_name.toStdString());
    VideoWriter writer;
    writer.open("E:/download/pictures/test.avi", writer.fourcc('M', 'J', 'P', 'G'), capture.get(CAP_PROP_FPS), Size(capture.get(CAP_PROP_FRAME_WIDTH), capture.get(CAP_PROP_FRAME_HEIGHT)));//注意此处视频的尺寸大小要与真实的一致

    ViBe vibe;
    bool count = true;
    double FPS = capture.get(CAP_PROP_FPS);//获取FPS  

    while (1)
    {
        if (!capture.isOpened())
        {
            cout << "No camera or video input!" << endl;
            return -1;
        }

        capture >> frame;
        if (frame.empty())
            break;
        //cvtColor(frame, gray, CV_RGB2GRAY);
        //if (count)
        //{
        //    vibe.init(gray);
        //    vibe.ProcessFirstFrame(gray);
        //    cout << "Training ViBe Success." << endl;
        //    count = false;
        //    writer.write(frame);
        //}
        //else
        //{
        //    vibe.Run(gray);

        //    FGModel = vibe.getFGModel();
        //    Mat diff;
        //    absdiff(gray, pre, diff);
        //    ////对差值图diff_thresh进行阈值化处理  二值化
        //    //Mat diff_thresh;
        //    //Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 3));//函数会返回指定形状和尺寸的结构元素。																 //调用之后，调用膨胀与腐蚀函数的时候，第三个参数值保存了getStructuringElement返回值的Mat类型变量。也就是element变量。
        //    //Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(18, 18));

        //    ////进行二值化处理，选择50，255为阈值
        //    //threshold(diff, diff_thresh, 50, 255, CV_THRESH_BINARY);
        //    ////膨胀  
        //    //dilate(diff_thresh, diff_thresh, kernel_dilate);
        //    ////腐蚀  
        //    //erode(diff_thresh, diff_thresh, kernel_erode);

        //    //查找轮廓并绘制轮廓  
        //    vector<vector<Point> > contours;
        //    findContours(diff, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//找轮廓函数
        //    //查找正外接矩形  
        //    //vector<Rect> boundRect(contours.size());
        //    //cout << contours.size() << endl;
        //    if (contours.size() > 1000) {
        //        writer.write(frame);
        //    }
        //    //imshow("FGModel", FGModel);
        //}
        //cvtColor(frame, pre, CV_RGB2GRAY);

        imshow("input", frame);

        waitKey(33);
    }
    //弹出完成对话框
    QMessageBox::about(NULL, "Successful", "Already slip the video!");

    return 0;
}
