#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include <QObject>
#include <QMouseEvent>
#include "imageitem.h"

class ImageItem;
class RectangleTool : public QObject
{
    Q_OBJECT
public:
    explicit RectangleTool(QObject *parent = 0);
        ~RectangleTool(){};

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

#endif // RECTANGLETOOL_H
