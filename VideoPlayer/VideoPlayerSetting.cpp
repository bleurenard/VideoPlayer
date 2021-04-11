#include "VideoPlayerSetting.h"
#include "opencv2/imgproc/types_c.h"
#include <iostream>
#include "Vibe.h"

using namespace std;

//��ʼ����̬����
bool VideoPlayerSetting::Is_Video_play = false;
VideoPlayerSetting::VideoPlayerSetting(QSlider* slider, QLabel* video_label, QLabel* label_pos, QLabel* label_total)
{
    //���캯��
    this->slider = slider;
    this->video_label = video_label;
    this->label_pos = label_pos;
    this->label_total = label_total;

}


void VideoPlayerSetting::show_img(Mat image, QLabel* label) {

    //    ��label����ʾopencvͼƬ
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
    //ֹͣ����
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
    //�򿪲�����
    Stop_Play = false;
}
void VideoPlayerSetting::Pase() {
    //��ͣ

    Is_Pase = true;

}
void VideoPlayerSetting::PaseOrStart() {
    //��ͣ
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
    //����frame��������λ��
    this->pos = po;
}
void VideoPlayerSetting::run() {
    //player���̺߳���
    while (true) {
        //�����������Ӧ �仯��ʼλ��
        if (pos != -1) {
            capture.set(1, pos);
            pos = -1;
        }
        //��ͣ��Ӧ
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
    writer.open("E:/download/pictures/test.avi", writer.fourcc('M', 'J', 'P', 'G'), capture.get(CAP_PROP_FPS), Size(capture.get(CAP_PROP_FRAME_WIDTH), capture.get(CAP_PROP_FRAME_HEIGHT)));//ע��˴���Ƶ�ĳߴ��СҪ����ʵ��һ��

    ViBe vibe;
    bool count = true;
    double FPS = capture.get(CAP_PROP_FPS);//��ȡFPS  

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
        //    ////�Բ�ֵͼdiff_thresh������ֵ������  ��ֵ��
        //    //Mat diff_thresh;
        //    //Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 3));//�����᷵��ָ����״�ͳߴ�ĽṹԪ�ء�																 //����֮�󣬵��������븯ʴ������ʱ�򣬵���������ֵ������getStructuringElement����ֵ��Mat���ͱ�����Ҳ����element������
        //    //Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(18, 18));

        //    ////���ж�ֵ������ѡ��50��255Ϊ��ֵ
        //    //threshold(diff, diff_thresh, 50, 255, CV_THRESH_BINARY);
        //    ////����  
        //    //dilate(diff_thresh, diff_thresh, kernel_dilate);
        //    ////��ʴ  
        //    //erode(diff_thresh, diff_thresh, kernel_erode);

        //    //������������������  
        //    vector<vector<Point> > contours;
        //    findContours(diff, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//����������
        //    //��������Ӿ���  
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
    //������ɶԻ���
    QMessageBox::about(NULL, "Successful", "Already slip the video!");

    return 0;
}
