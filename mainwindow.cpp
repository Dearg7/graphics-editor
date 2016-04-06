#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageitem.h"
#include "tools/penciltool.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ImageItem *image = new ImageItem();
    ui->scrollArea->setBackgroundRole(QPalette :: Dark);
    ui->scrollArea->setWidget(image);



}

MainWindow::~MainWindow()
{
    delete ui;
}
