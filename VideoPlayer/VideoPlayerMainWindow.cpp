#include "VideoPlayerMainWindow.h"

VideoPlayerMainWindow::VideoPlayerMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //连接相关信号与槽
    connect(ui.open_btn, SIGNAL(clicked(bool)), this, SLOT(Open_video_Slot()));
    connect(ui.frame_handle_btn, SIGNAL(clicked(bool)), this, SLOT(Frame_handle_Slot()));
    connect(ui.start_btn, SIGNAL(clicked(bool)), this, SLOT(start_btn_Slot()));

    //ui.choose_btn->setVisible(false);
}

void VideoPlayerMainWindow::Frame_handle_Slot() {
    player->Video_Slip(file_name);
    // exit(0);
}
void VideoPlayerMainWindow::Open_video_Slot() {
    /*打开视频按钮槽函数*/
    //选择视频文件
    file_name = QFileDialog::getOpenFileName(this, tr("选择视频文件"), "E:\\BaiduNetdiskDownload",tr("视频格式(*.avi *.mp4 *.flv *.mkv)"));
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly))
    {

        return;
    }
    else {
        if (player == NULL) {
            //当没有视频播放时
            player = new VideoPlayerSetting(ui.slider, ui.video_label, ui.label_pos, ui.label_total);
            player->play(file_name);
            //开启线程
            QThreadPool::globalInstance()->start(player);
        }
        else {
            //当有视频播放时
            player->Stop();
            player->play(file_name);
        }
    }
}
VideoPlayerMainWindow::~VideoPlayerMainWindow()
{
    delete ui.centralWidget;
}
void VideoPlayerMainWindow::start_btn_Slot() {
    player->PaseOrStart();
}
void VideoPlayerMainWindow::on_pushButton_clicked()
{
    int s = player->Slower();
    //慢放按钮
    ui.label_mag->setText(QString::number((30 - s) / 5) + "X");
}

void VideoPlayerMainWindow::on_pushButton_2_clicked()
{
    //快进按钮
    int s = player->Faster();
    ui.label_mag->setText(QString::number((30 - s) / 5) + "X");
}

void VideoPlayerMainWindow::on_slider_sliderMoved(int position)
{
    //拖动进度条响应 PaseOrStart在这里非常重要,实现了拖动时的动态变化
    player->PaseOrStart();
    player->Set_postion(ui.slider->value());
}

void VideoPlayerMainWindow::on_slider_sliderPressed()
{
}

//void VideoPlayerMainWindow::on_choose_btn_clicked()
//{
//    switch (frame_hanle_from->mode) {
//    case 1:
//        frame_hanle_from->mode1_text1->setText(QString::number(player->get_current_pos()));
//        frame_hanle_from->show();
//        break;
//    case 2:
//        frame_hanle_from->mode1_text2->setText(QString::number(player->get_current_pos()));
//        frame_hanle_from->show();
//        break;
//    case 3:
//        frame_hanle_from->mode3_text->setText(QString::number(player->get_current_pos()));
//        frame_hanle_from->show();
//        break;
//    }
//}

void VideoPlayerMainWindow::vedioProcessing()
{

}
