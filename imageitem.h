#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QImage>
#include <tools/penciltool.h>
#include <tools/erasertool.h>
#include <tools/ellipsetool.h>
#include "undostack.h"



class PencilTool;
class EraserTool;
class EllipseTool;
class UndoStack;
class ImageItem : public QWidget
{
    Q_OBJECT
public:
    explicit ImageItem(QWidget *parent = 0);
    ~ImageItem();

   QImage *getImage ();
   void setImage(QImage img);
   QColor getColor1();
   QColor getColor2();
   int getSize();
   UndoStack *getUndoStack();



private:
    UndoStack *UStack;
    QString currentFile;
    QImage *_image ;
    PencilTool *pen ;
    EraserTool *eraser;
    EllipseTool *ellipse;
    QColor *color1;
    QColor *color2;
    QRect imageRect;
    int size;
    bool pencilCheck;
    bool eraserCheck;
    bool ellipseCheck;


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
    void open();
    void saveAs();
    void save();
    void setPencil(const bool b);
    void setEraser(const bool b);
    void setEllipse(const bool b);
};

#endif // IMAGEITEM_H
