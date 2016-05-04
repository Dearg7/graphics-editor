#ifndef LINETOOL_H
#define LINETOOL_H
#include <QMouseEvent>
#include "imageitem.h"

class ImageItem;
class LineTool : public QObject
{
    Q_OBJECT
public:
    explicit LineTool(QObject *parent = 0);
        ~LineTool(){};


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

#endif // LINETOOL_H
