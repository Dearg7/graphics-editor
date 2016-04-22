#include "imageitem.h"
#include "mainwindow.h"
#include <QApplication>
#include "widgets/colorselection.h"
#include "QHBoxLayout"
#include <QTextCodec>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    MainWindow w;

    w.show();
    /*ImageItem ww;
    ww.show();
    QWidget *W = new QWidget();
    QHBoxLayout *L = new QHBoxLayout();
    ColorSelection *SR = new ColorSelection(Qt::black);
    L->addWidget(SR);
    W->setLayout(L);
    W->show();*/



    return a.exec();
}
