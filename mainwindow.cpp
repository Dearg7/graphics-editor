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
#include <QToolBar>
#include <QActionGroup>
#include <QPushButton>
#include <QSpinBox>


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
    QObject::connect(image->getPipette(),SIGNAL(changeColor1(QColor)),CS1,SLOT(setColor(QColor)));
    QObject::connect(CS2,SIGNAL(changeColor(QColor)),image,SLOT(setColor2(QColor)));
    QObject::connect(image->getPipette(),SIGNAL(changeColor2(QColor)),CS2,SLOT(setColor(QColor)));
    QHBoxLayout *Hlayout = new QHBoxLayout();
    Hlayout->addStretch(5);
    Hlayout->addWidget(CS1);
    Hlayout->addWidget(CS2);
    Hlayout->addStretch(5);

   // create slider
    QHBoxLayout *SSBlayout = new QHBoxLayout();
    SSBlayout->addWidget(image->getSlider());
    SSBlayout->addWidget(image->getSpinBox());


    QVBoxLayout *Blayout = new QVBoxLayout();
    Blayout->addLayout(SSBlayout);
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

    QHBoxLayout *topLayout = new QHBoxLayout();
    QPushButton *plusZoom = new QPushButton();

    plusZoom->setIcon(QIcon(":/res/icons/zoomin.png"));
    plusZoom->setIconSize(QSize(30,30));
    plusZoom->setPalette(Qt::transparent);
    plusZoom->setFixedSize(35,35);

    QPushButton *minusZoom = new QPushButton();
    QSlider *zoomSlider = new QSlider(Qt::Horizontal);
    minusZoom->setIcon(QIcon(":/res/icons/zoomout.png"));
    minusZoom->setIconSize(QSize(30,30));
    minusZoom->setPalette(Qt::transparent);
    minusZoom->setFixedSize(35,35);

    zoomSlider->setMaximum(20);
    zoomSlider->setMinimum(1);
    zoomSlider->setValue(4);
    zoomSlider->setPageStep(2);
    zoomSlider->setFixedWidth(100);

    QLabel *zoomLabel = new QLabel();
    zoomLabel->setNum(100);
    QObject::connect(image,SIGNAL(changeZoom2(int)),zoomLabel,SLOT(setNum(int)));
    QObject::connect(zoomSlider,SIGNAL(valueChanged(int)),image,SLOT(setZoom(int)));
    QObject::connect(image,SIGNAL(changeZoom(int)),zoomSlider,SLOT(setValue(int)));
    topLayout->setSpacing(0);
    topLayout->addStretch(2000);
    topLayout->addWidget(minusZoom);


    topLayout->addWidget(zoomSlider);

    topLayout->addWidget(plusZoom);
     topLayout->addSpacing(5);
    topLayout->addWidget(zoomLabel);
    QLabel *proc = new QLabel("%");
    topLayout->addWidget(proc);
    topLayout->setContentsMargins(0,0,0,0);

    QWidget *zoom = new QWidget();
    zoom->setLayout(topLayout);

    QToolBar *ToolBar = new QToolBar;
    ToolBar->setAllowedAreas(Qt::BottomToolBarArea);
    ToolBar->setFloatable(false);
    ToolBar->setMovable(false);

     ToolBar->addWidget(zoom);

    addToolBar(Qt::BottomToolBarArea,ToolBar);


// zooming
    QObject::connect(plusZoom,SIGNAL(clicked(bool)),image,SLOT(zoomPlus()));
    QObject::connect(minusZoom,SIGNAL(clicked(bool)),image,SLOT(zoomMinus()));

    QActionGroup *GP = new QActionGroup(this);
    GP->addAction(ui->actionPencil);
    GP->addAction(ui->actionEraser);
    GP->addAction(ui->actionEllipse);
    GP->addAction(ui->actionRectangle);
    GP->addAction(ui->actionLine);
    GP->addAction(ui->actionCurveLine);
    GP->addAction(ui->actionFill);
    GP->addAction(ui->actionPipette);
    GP->addAction(ui->actionSelection);
    GP->setExclusive(true);

    //create tool bar
    QToolBar *TB = new QToolBar();
    TB->setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea);
    TB->setFloatable(false);
    TB->setMovable(true);

    TB->insertAction(0,ui->actionSaveAs);
    TB->insertAction(ui->actionSaveAs,ui->actionSave);
    TB->insertAction(ui->actionSave,ui->actionOpen);
    TB->insertAction(ui->actionOpen,ui->actionCreate);
    TB->addSeparator();
    TB->insertAction(0,ui->actionRedo);
    TB->insertAction(ui->actionRedo,ui->actionUndo);
    TB->addSeparator();
    TB->insertAction(0,ui->actionSelection);
    TB->insertAction(ui->actionSelection,ui->actionPipette);
    TB->insertAction(ui->actionPipette,ui->actionFill);
    TB->insertAction(ui->actionFill,ui->actionCurveLine);
    TB->insertAction(ui->actionCurveLine,ui->actionLine);
    TB->insertAction(ui->actionLine,ui->actionRectangle);
    TB->insertAction(ui->actionRectangle,ui->actionEllipse);
    TB->insertAction(ui->actionEllipse,ui->actionEraser);
    TB->insertAction(ui->actionEraser,ui->actionPencil);




    addToolBar(Qt::TopToolBarArea, TB);
    // create action connecting
    QObject::connect(ui->actionOpen,SIGNAL(triggered(bool)),image,SLOT(open()));
    QObject::connect(ui->actionSaveAs,SIGNAL(triggered(bool)),image,SLOT(saveAs()));
    QObject::connect(ui->actionSave,SIGNAL(triggered(bool)),image,SLOT(save()));
    QObject::connect(ui->actionCreate,SIGNAL(triggered(bool)),image,SLOT(create()));
    QObject::connect(ui->actionPencil,SIGNAL(toggled(bool)),image,SLOT(setPencil(bool)));
    QObject::connect(ui->actionEraser,SIGNAL(toggled(bool)),image,SLOT(setEraser(bool)));
    QObject::connect(ui->actionEllipse,SIGNAL(toggled(bool)),image,SLOT(setEllipse(bool)));
    QObject::connect(ui->actionRectangle,SIGNAL(toggled(bool)),image,SLOT(setRectangle(bool)));
    QObject::connect(ui->actionLine,SIGNAL(toggled(bool)),image,SLOT(setLine(bool)));
    QObject::connect(ui->actionCurveLine,SIGNAL(toggled(bool)),image,SLOT(setCurveLine(bool)));
    QObject::connect(ui->actionFill,SIGNAL(toggled(bool)),image,SLOT(setFill(bool)));
    QObject::connect(ui->actionFill,SIGNAL(toggled(bool)),image,SLOT(senseFill(bool)));
    QObject::connect(ui->actionPipette,SIGNAL(toggled(bool)),image,SLOT(setPipette(bool)));
    QObject::connect(ui->actionSelection,SIGNAL(toggled(bool)),image,SLOT(setSelection(bool)));
    QObject::connect(ui->actionChange,SIGNAL(triggered(bool)),image,SLOT(change()));
    //undo and redo
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    QObject::connect(image->getUndoStack(),SIGNAL(canUndo(bool)),ui->actionUndo,SLOT(setEnabled(bool)));
    QObject::connect(ui->actionUndo,SIGNAL(triggered(bool)),image->getUndoStack(),SLOT(undo()));
    QObject::connect(image->getUndoStack(),SIGNAL(canRedo(bool)),ui->actionRedo,SLOT(setEnabled(bool)));
    QObject::connect(image->getUndoStack(),SIGNAL(canRedo(bool)),image,SLOT(setNewCurve(bool)));
    QObject::connect(ui->actionRedo,SIGNAL(triggered(bool)),image->getUndoStack(),SLOT(redo()));

    //copy and cut and put

    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionPut->setEnabled(false);
    QObject::connect(image->getSelection(),SIGNAL(canCopy(bool)),ui->actionCopy,SLOT(setEnabled(bool)));
    QObject::connect(ui->actionCopy,SIGNAL(triggered(bool)),image,SLOT(makeCopy()));
    QObject::connect(image->getSelection(),SIGNAL(canCopy(bool)),ui->actionCut,SLOT(setEnabled(bool)));
    QObject::connect(ui->actionCut,SIGNAL(triggered(bool)),image,SLOT(makeCut()));
    QObject::connect(image->getSelection(),SIGNAL(canPut(bool)),ui->actionPut,SLOT(setEnabled(bool)));
    QObject::connect(ui->actionPut,SIGNAL(triggered(bool)),image,SLOT(makePut()));
    QObject::connect(ui->actionSelection,SIGNAL(changed()),image,SLOT(clearSelection()));


    ui->scrollArea->setBackgroundRole(QPalette :: Dark);
    ui->scrollArea->setWidget(image);





}

MainWindow::~MainWindow()
{
    delete ui;
}
