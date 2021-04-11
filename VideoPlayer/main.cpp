#include "VideoPlayerMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoPlayerMainWindow w;
    w.show();
    return a.exec();
}
