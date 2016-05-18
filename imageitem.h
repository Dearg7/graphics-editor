#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QImage>
#include <QDebug>
#include <QSlider>
#include <QSpinBox>
#include <tools/penciltool.h>
#include <tools/erasertool.h>
#include <tools/ellipsetool.h>
#include <tools/rectangletool.h>
#include <tools/linetool.h>
#include <tools/curvelinetool.h>
#include <tools/filltool.h>
#include <tools/pipettetool.h>
#include <tools/selectiontool.h>
#include "undostack.h"



class PencilTool;
class EraserTool;
class EllipseTool;
class RectangleTool;
class LineTool;
class CurveLineTool;
class FillTool;
class PipetteTool;
class SelectionTool;
class UndoStack;
class ImageItem : public QWidget
{
    Q_OBJECT
public:
    explicit ImageItem(QWidget *parent = 0);
    ~ImageItem();

   QImage *getImage ();
   bool getNewCurve();
   void setImage(QImage img);
   QColor getColor1();
   QColor getColor2();
   PipetteTool *getPipette();
   int getSize();
   UndoStack *getUndoStack();
   SelectionTool *getSelection();
   double getZoom();
   QSlider *getSlider();
   QSpinBox *getSpinBox();



private:
    UndoStack *UStack;
    QString currentFile;
    QImage *_image ;
    PencilTool *pen ;
    EraserTool *eraser;
    EllipseTool *ellipse;
    RectangleTool *rectangle;
    CurveLineTool *curveLine;
    FillTool *fill;
    LineTool *line;
    PipetteTool *pipette;
    SelectionTool *selection;
    QColor *color1;
    QColor *color2;
    QRect imageRect;
    QSize imageSize;
    int size;
    int copySize;
    int cWidth,cHeight;
    double iZoom,prevZoom;
    bool newCurve;
    bool pencilCheck;
    bool eraserCheck;
    bool ellipseCheck;
    bool rectangleCheck;
    bool lineCheck;
    bool curveLineCheck;
    bool fillCheck;
    bool pipetteCheck;
    bool selectionCheck;

    QSlider *slider;
    QSpinBox *spinBox;


    void zooming();



protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);




signals:



public slots:
    void setColor1(const QColor _color);
    void setColor2(const QColor _color);
    void setSize(const int _size);
    void senseFill(const bool b);
    void open();
    void saveAs();
    void save();
    void setNewCurve(const bool b);
    void setPencil(const bool b);
    void setEraser(const bool b);
    void setEllipse(const bool b);
    void setRectangle(const bool b);
    void setLine(const bool b);
    void setCurveLine(const bool b);
    void setFill(const bool b);
    void setPipette(const bool b);
    void setSelection(const bool b);
    void makeCopy();
    void makeCut();
    void makePut();
    void clearSelection();
    void zoomPlus();
    void zoomMinus();
    void change();
    void changeWidth(int w);
    void changeHeight(int h);
    void changeAccept();


};

#endif // IMAGEITEM_H
