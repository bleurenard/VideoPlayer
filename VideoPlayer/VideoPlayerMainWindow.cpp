#include "VideoPlayerMainWindow.h"

VideoPlayerMainWindow::VideoPlayerMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //��������ź����
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
    /*����Ƶ��ť�ۺ���*/
    //ѡ����Ƶ�ļ�
    file_name = QFileDialog::getOpenFileName(this, tr("ѡ����Ƶ�ļ�"), "E:\\BaiduNetdiskDownload",tr("��Ƶ��ʽ(*.avi *.mp4 *.flv *.mkv)"));
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly))
    {

        return;
    }
    else {
        if (player == NULL) {
            //��û����Ƶ����ʱ
            player = new VideoPlayerSetting(ui.slider, ui.video_label, ui.label_pos, ui.label_total);
            player->play(file_name);
            //�����߳�
            QThreadPool::globalInstance()->start(player);
        }
        else {
            //������Ƶ����ʱ
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
    //���Ű�ť
    ui.label_mag->setText(QString::number((30 - s) / 5) + "X");
}

void VideoPlayerMainWindow::on_pushButton_2_clicked()
{
    //�����ť
    int s = player->Faster();
    ui.label_mag->setText(QString::number((30 - s) / 5) + "X");
}

void VideoPlayerMainWindow::on_slider_sliderMoved(int position)
{
    //�϶���������Ӧ PaseOrStart������ǳ���Ҫ,ʵ�����϶�ʱ�Ķ�̬�仯
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
