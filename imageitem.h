#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QImage>
#include <tools/penciltool.h>

class PencilTool;

class ImageItem : public QWidget
{
    Q_OBJECT
public:
    explicit ImageItem(QWidget *parent = 0);
    ~ImageItem();

   QImage *getImage ();
   QColor getColor1();
   QColor getColor2();
   int getSize();
   QString currentFile;


private:
    QImage *_image ;
    PencilTool *pen ;
    QColor *color1;
    QColor *color2;
    QRect imageRect;
    int size;



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
};

#endif // IMAGEITEM_H
