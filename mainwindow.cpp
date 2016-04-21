#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageitem.h"
#include "tools/penciltool.h"
#include "widgets/colorselection.h"
#include <QObject>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ImageItem *image = new ImageItem();
    ColorSelection *CS1 = new ColorSelection(Qt::black);
    ColorSelection *CS2 = new ColorSelection(Qt::white);
    QObject::connect(CS1,SIGNAL(changeColor(QColor)),image,SLOT(setColor1(QColor)));
    QObject::connect(CS2,SIGNAL(changeColor(QColor)),image,SLOT(setColor2(QColor)));
    ui->scrollArea->setBackgroundRole(QPalette :: Dark);
    ui->scrollArea->setWidget(image);
    CS1->show();
    CS2->show();



}

MainWindow::~MainWindow()
{
    delete ui;
}
