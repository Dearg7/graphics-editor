#include "imageitem.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;

    w.show();
    ImageItem ww;
    ww.show();



    return a.exec();
}
