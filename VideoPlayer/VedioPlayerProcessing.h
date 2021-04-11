#pragma once
#include <QWidget>
#include <QDebug>
#include <QThreadPool>
#include <QProgressBar>
#include <QThread>
#include <QDebug>
#include <string.h>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include <QLineEdit>
#include <QRunnable>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QStringList>
#include <highgui.hpp>
using namespace cv;
namespace Ui {
    class VedioPlayerProcessing;
}

class VedioPlayerProcessing : public QWidget
{
    Q_OBJECT

public:
    explicit VedioPlayerProcessing(QWidget* parent = 0);
//    ~VedioPlayerProcessing();
//    QLineEdit* mode1_text1;
//    QLineEdit* mode1_text2;
//    QLineEdit* mode3_text;
//    QString Video_Path;
//    VideoCapture capture;
//    int mode = -1;
//
//private slots:
//    void  mode_switch();
//    void on_mode3_time_btn_clicked();
//    void on_mode1_start_btn_clicked();
//    void on_mode1_stop_btn_clicked();
//    void on_mode1_ok_btn_clicked();
//    void on_mode2_ok_btn_clicked();
//    void on_mode1_path_btn_clicked();
//
//    void on_mode2_path_btn_clicked();
//
//    void on_mode3_path_btn_clicked();
//
//    void on_mode4_imgpath_btn_clicked();
//
//    void on_mode4_path_btn_clicked();
//
//    void on_mode3_ok_btn_clicked();
//
//    void on_mode4_ok_btn_clicked();

private:
    Ui::VedioPlayerProcessing* ui;
//};
//
////ģʽ1��handle��
//class Model1 : public QRunnable
//{
//public:
//    Model1(QString path, QString save_path, double starttime, double stoptime, QProgressBar* bar)
//    {
//        this->path = path;
//        this->save_path = save_path;
//        this->bar = bar;
//        this->starttime = starttime;
//        this->stoptime = stoptime;
//    }
//
//private:
//    QString path;
//    QString save_path;
//    QProgressBar* bar;
//    double starttime;
//    double stoptime;
//    void run() {
//        // �ܳ����Ժ����
//        double total = stoptime - starttime;
//        // ����֡
//        VideoCapture capture;
//        capture.open(path.toStdString());
//        Mat image;// ����һ��Mat����������һ֡��ͼ��
//        capture.read(image);
//
//        VideoWriter writer;
//        // ��ȡ��Ƶ֡
//        capture.set(0, starttime);
//        // ��ǰ����ʱ�����Ժ����
//
//        while (capture.read(image)) {
//            double time = capture.get(0);
//            double curr = (double)(time - starttime);
//            // �ٷֱȣ���ǿתΪ float
//            int percent = (curr / total) * 100;
//            QMetaObject::invokeMethod(bar, "setValue", Qt::QueuedConnection, Q_ARG(int, percent));
//            if (time >= stoptime) {
//                break;
//            }
//            imwrite(save_path.toStdString() + "/" + QString::number(time).toStdString() + ".jpg", image);
//        }
//        bar->setVisible(false);
//    }
//};
//
////ģʽ2��handle��
//class Model2 : public QRunnable
//{
//public:
//    Model2(QString path, QString save_path, double intevel_time, QProgressBar* bar)
//    {
//        this->path = path;
//        this->savepath = save_path;
//        this->bar = bar;
//        this->splittime = intevel_time;
//    }
//
//private:
//    QString path;
//    QString savepath;
//    QProgressBar* bar;
//    double splittime;
//    void run() {
//        VideoCapture capture;
//        capture.open(path.toStdString());
//        long starttime = 0;
//        long stoptime = (long)capture.get(7);
//        long total = stoptime - starttime;
//        Mat image;// ����һ��Mat����������һ֡��ͼ��
//        capture.read(image);
//        VideoWriter writer;
//        // ��ȡ��Ƶ֡
//        capture.set(0, starttime);
//        // ��ǰ����ʱ�����Ժ����
//        long time_flag = 0;
//        long flag = 0;
//        QString savepath2 = "";
//        while (capture.read(image)) {
//            double time = capture.get(0);
//            long curr = (long)capture.get(1);
//            double currs = curr;
//            // �ٷֱȣ���ǿתΪ float
//            int percent = (currs / total) * 100;
//            QMetaObject::invokeMethod(bar, "setValue", Qt::QueuedConnection, Q_ARG(int, percent));
//            qDebug() << "��ǰʱ�䣺" + QString::number(time);
//
//            if (int(time) % int(splittime) == 0) {
//                savepath2 = savepath + "/" + QString::number(flag);
//                //���·�������ڣ��򴴽�
//                QDir* dir = new QDir();
//                if (!dir->exists(savepath2)) {
//                    dir->mkpath(savepath2);
//                }
//                flag++;
//            }
//            qDebug() << savepath2 + "/" + QString::number(time) + ".jpg";
//            imwrite(savepath2.toStdString() + "/" + QString::number(time).toStdString() + ".jpg", image);
//
//        }
//        bar->setVisible(false);
//    }
//};
////ģʽ4��handle��
//class Model4 : public QRunnable
//{
//public:
//    Model4(QString path, QString save_path, double rate, QProgressBar* bar)
//    {
//        this->path = path;
//        this->savepath = save_path;
//        this->bar = bar;
//        this->rate = rate;
//    }
//
//private:
//    QString path;
//    QString savepath;
//    QProgressBar* bar;
//    QDir dir;
//    double rate;
//    QStringList img_list;
//    double splittime;
//    QStringList nameFilters;
//    void run() {
//        bar->setVisible(true);
//        //��ȡ�ļ��������е��ļ�
//        dir.setPath(path);
//        //���ö�ȡ���ļ��ĸ�ʽ
//        nameFilters << "*.jpg" << "*.png" << "*.tif";
//        dir.setFilter(QDir::Files | QDir::NoSymLinks); //�������͹�������ֻΪ�ļ���ʽ
//        dir.setNameFilters(nameFilters);
//        for (int i = 0; i < dir.count(); i++) {
//            img_list.append(path + "/" + dir[i]);
//
//        }
//        img_list.sort();
//        Mat img = imread(img_list[0].toStdString());
//        VideoWriter* writer = new VideoWriter(savepath.toStdString(),
//            CAP_OPENCV_MJPEG, rate,
//            Size(img.cols, img.rows));
//
//        for (int i = 0; i < img_list.size(); i++) {
//            img = imread(img_list[i].toStdString());
//            writer->write(img);
//            double curr = i;
//            // �ٷֱȣ���ǿתΪ float
//            int percent = (curr / img_list.size()) * 100;
//            qDebug() << curr / img_list.size() << " " << percent << endl;
//            QMetaObject::invokeMethod(bar, "setValue", Qt::QueuedConnection, Q_ARG(int, percent));
//        }
//        bar->setVisible(false);
//
//    }
};