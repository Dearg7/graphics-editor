#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageitem.h"
#include "tools/penciltool.h"
#include "widgets/colorselection.h"
#include <QObject>
#include <QDockWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->resize(800,680);
    this->setWindowState(Qt::WindowMaximized);
    ImageItem *image = new ImageItem();

    //create ColorSelection
    ColorSelection *CS1 = new ColorSelection(Qt::black);
    ColorSelection *CS2 = new ColorSelection(Qt::white);
    QObject::connect(CS1,SIGNAL(changeColor(QColor)),image,SLOT(setColor1(QColor)));
    QObject::connect(CS2,SIGNAL(changeColor(QColor)),image,SLOT(setColor2(QColor)));
    QHBoxLayout *Hlayout = new QHBoxLayout();
    Hlayout->addStretch(5);
    Hlayout->addWidget(CS1);
    Hlayout->addWidget(CS2);
    Hlayout->addStretch(5);

    //Create slider
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setMaximum(100);
    slider->setMinimum(1);
    slider->setValue(10);
    QObject::connect(slider,SIGNAL(valueChanged(int)),image,SLOT(setSize(int)));


    QVBoxLayout *Blayout = new QVBoxLayout();
    Blayout->addWidget(slider);
    Blayout->addLayout(Hlayout);
    QWidget *wdg = new QWidget();
    wdg->setLayout(Blayout);
    // Create Dock
    //
    //
    QDockWidget *dock = new QDockWidget(tr("Настройка"),this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    wdg->setFixedSize(200,100);
    dock->setWidget(wdg);
    dock->setMaximumHeight(300);
    dock->setMaximumWidth(300);

    addDockWidget(Qt::RightDockWidgetArea,dock);
    // create action connecting
    QObject::connect(ui->actionOpen,SIGNAL(triggered(bool)),image,SLOT(open()));
    QObject::connect(ui->actionSaveAs,SIGNAL(triggered(bool)),image,SLOT(saveAs()));
    QObject::connect(ui->actionSave,SIGNAL(triggered(bool)),image,SLOT(save()));

    //undo and redo
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    QObject::connect(image->getUndoStack(),SIGNAL(canUndo(bool)),ui->actionUndo,SLOT(setEnabled(bool)));
    QObject::connect(ui->actionUndo,SIGNAL(triggered(bool)),image->getUndoStack(),SLOT(undo()));
    QObject::connect(image->getUndoStack(),SIGNAL(canRedo(bool)),ui->actionRedo,SLOT(setEnabled(bool)));
    QObject::connect(ui->actionRedo,SIGNAL(triggered(bool)),image->getUndoStack(),SLOT(redo()));


    ui->scrollArea->setBackgroundRole(QPalette :: Dark);
    ui->scrollArea->setWidget(image);





}

MainWindow::~MainWindow()
{
    delete ui;
}
