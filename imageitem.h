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


private:
    QImage *_image ;
    PencilTool *pen ;



protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);



signals:

public slots:
};

#endif // IMAGEITEM_H
