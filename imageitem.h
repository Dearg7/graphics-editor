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


private:
    QImage *_image ;
    PencilTool *pen ;
    QColor *color1;
    QColor *color2;



protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);




signals:


public slots:
    void setColor1(const QColor _color);
    void setColor2(const QColor _color);
};

#endif // IMAGEITEM_H
