//#include "VedioPlayerProcessing.h"
//#include "ui_VedioPlayerProcessing.h"
//
//VedioPlayerProcessing::VedioPlayerProcessing(QWidget* parent) :
//    QWidget(parent)
//{
//    ui.setupUi(this);
//    ui.stackedWidget->setCurrentIndex(0);
//    mode1_text1 = ui.mode1_start_text;
//    mode1_text2 = ui.mode1_stop_text;
//    mode3_text = ui.mode3_time_text;
//    //������زۺ���
//    connect(ui.mode1_btn, SIGNAL(clicked(bool)), this, SLOT(mode_switch()));
//    connect(ui.mode2_btn, SIGNAL(clicked(bool)), this, SLOT(mode_switch()));
//    connect(ui.mode3_btn, SIGNAL(clicked(bool)), this, SLOT(mode_switch()));
//    connect(ui.mode4_btn, SIGNAL(clicked(bool)), this, SLOT(mode_switch()));
//    ui.progressBar1->setVisible(false);
//    ui.progressBar_2->setVisible(false);
//    ui.progressBar_3->setVisible(false);
//    ui.progressBar_4->setVisible(false);
//}
//
//
//void VedioPlayerProcessing::on_mode3_time_btn_clicked()
//{
//    //��ȡ��֡
//    this->hide();
//    this->mode = 3;
//}
//
//void VedioPlayerProcessing::on_mode1_start_btn_clicked()
//{
//    //�Զ����֡
//    this->hide();
//    this->mode = 1;
//}
//
//void VedioPlayerProcessing::on_mode1_stop_btn_clicked()
//{
//    //�Զ����֡
//    this->hide();
//    this->mode = 2;
//}
//void VedioPlayerProcessing::on_mode1_path_btn_clicked()
//{
//    //ģʽ1�������ť
//    QString file_path = QFileDialog::getExistingDirectory(this, "��ѡ���ļ�����·��...", "./");
//    if (file_path.isEmpty())
//    {
//        return;
//    }
//    else {
//        ui.mode1_path_text->setText(file_path);
//    }
//}
//
//void VedioPlayerProcessing::on_mode2_path_btn_clicked()
//{
//    //ģʽ2�������ť
//    QString file_path = QFileDialog::getExistingDirectory(this, "��ѡ���ļ�����·��...", "./");
//    if (file_path.isEmpty())
//    {
//        return;
//    }
//    else {
//        ui.mode2_path_text->setText(file_path);
//    }
//}
//void VedioPlayerProcessing::on_mode3_path_btn_clicked()
//{
//    //ģʽ3�������ť
//    QString reSave_path = QFileDialog::getSaveFileName(this, tr("����Ϊ"), "", "��ͨͼ��(*.jpg *.png *.bmp);;ң��ͼ��(*.tif)"); //ѡ��·��
//    ui.mode3_path_text->setText(reSave_path);
//
//
//}
//
//void VedioPlayerProcessing::on_mode4_imgpath_btn_clicked()
//{
//    //ģʽ4��ͼƬλ�������ť
//    QString file_path = QFileDialog::getExistingDirectory(this, "��ѡ��ͼƬ֡����·��...", "./");
//    if (file_path.isEmpty())
//    {
//        return;
//    }
//    else {
//        ui.mode4_imgpath_text->setText(file_path);
//    }
//}
//void VedioPlayerProcessing::on_mode4_path_btn_clicked()
//{
//    //ģʽ4����Ƶλ�������ť
//    QString file_name = QFileDialog::getSaveFileName(this, tr("ѡ�񱣴���Ƶ�ļ���"), ".",
//        tr("��Ƶ��ʽ(*.avi *.mp4 *.flv *.mkv)"));
//
//
//    ui.mode4_path_text->setText(file_name);
//    QFile file(file_name);
//
//}
//
//void VedioPlayerProcessing::on_mode1_ok_btn_clicked()
//{
//    //�鿴��û��Ŀ¼,û�д���
//    QDir* dir = new QDir(ui.mode1_path_text->text());
//    if (!dir->exists()) {
//        dir->mkpath(ui.mode1_path_text->text());
//    }
//    //�Զ���ȷ�����
//    ui.progressBar1->setValue(0);
//    ui.progressBar1->setVisible(true);
//    Model1* m1_task = new Model1(Video_Path, ui->mode1_path_text->text(), ui->mode1_start_text->text().toDouble(),
//        ui->mode1_stop_text->text().toDouble(), ui->progressBar1);
//    QThreadPool::globalInstance()->start(m1_task);
//
//}
//
//void Frame_Handle_Form::on_mode2_ok_btn_clicked()
//{  //��ʱ����֡ȷ����ť����¼�
//    //�鿴��û��Ŀ¼,û�д���
//    QDir* dir = new QDir(ui->mode2_path_text->text());
//    if (!dir->exists()) {
//        dir->mkpath(ui->mode2_path_text->text());
//    }
//    ui->progressBar_2->setValue(0);
//    ui->progressBar_2->setVisible(true);
//    Model2* m2_task = new Model2(Video_Path, ui->mode2_path_text->text(),
//        ui->mode2_time_text->text().toDouble(), ui->progressBar_2);
//    QThreadPool::globalInstance()->start(m2_task);
//}
//
//
//void Frame_Handle_Form::on_mode3_ok_btn_clicked()
//{
//    //��ȡ��֡���水ť
//    capture.open(Video_Path.toStdString());
//    capture.set(0, ui->mode3_time_text->text().toInt());
//    Mat frame;
//    capture.read(frame);
//    ui->progressBar_3->setVisible(true);
//    ui->progressBar_3->setValue(0);
//    imwrite(ui->mode3_path_text->text().toStdString(), frame);
//    ui->progressBar_3->setValue(100);
//    ui->progressBar_3->setVisible(false);
//}
//void Frame_Handle_Form::on_mode4_ok_btn_clicked()
//{
//    //֡�ϳ���Ƶȷ����ť
//    Model4* m4_task = new Model4(ui->mode4_imgpath_text->text(), ui->mode4_path_text->text(), ui->mode4_rate_text->text().toDouble(), ui->progressBar_4);
//    QThreadPool::globalInstance()->start(m4_task);
//
//}
//Frame_Handle_Form::~Frame_Handle_Form()
//{
//    delete ui;
//}
//void Frame_Handle_Form::mode_switch() {
//    // ��ȡ�����źŵĶ����ŵ� QObject ���������
//    QObject* obj = sender();
//    // �ѻ������ǿ��ת�����������
//    QPushButton* button = dynamic_cast<QPushButton*>(obj);
//    // ��ȡ��������ı������жϳ��ǵ����ĸ���ť
//
//    QString text = button->text();
//    if (text == "�Զ����֡") {
//        ui->stackedWidget->setCurrentIndex(0);
//    }
//    else if (text == "�ȳ���֡") {
//        ui->stackedWidget->setCurrentIndex(1);
//    }
//    else if (text == "��ȡ��֡") {
//        ui->stackedWidget->setCurrentIndex(2);
//    }
//    else if (text == "��Ƶ�ϳ�") {
//        ui->stackedWidget->setCurrentIndex(3);
//    }
//
//
//}
