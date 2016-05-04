#ifndef ELLIPSETOOL_H
#define ELLIPSETOOL_H

#include <QObject>
#include <QMouseEvent>
#include <QImage>
#include "imageitem.h"

class ImageItem;
class EllipseTool : public QObject
{
    Q_OBJECT
public:
    explicit EllipseTool(QObject *parent = 0);
        ~EllipseTool(){};

    void mousePressEvent(QMouseEvent *event,ImageItem *image);
    void mouseMoveEvent(QMouseEvent *event,ImageItem *image);
    void mouseReleaseEvent(QMouseEvent *event,ImageItem *image);

private:
    QPoint BeginPoint,EndPoint;
    QImage imageCopy;
    void paint(ImageItem *image,bool check);

signals:

public slots:
};

#endif // ELLIPSETOOL_H
