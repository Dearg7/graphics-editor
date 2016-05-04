#ifndef ERASERTOOL_H
#define ERASERTOOL_H

#include <QObject>
#include <QMouseEvent>
#include "imageitem.h"
class ImageItem;
class EraserTool : public QObject
{
    Q_OBJECT
public:
    explicit EraserTool(QObject *parent = 0);
        ~EraserTool(){};

    void mousePressEvent(QMouseEvent *event,ImageItem *image);
    void mouseMoveEvent(QMouseEvent *event,ImageItem *image);
    void mouseReleaseEvent(QMouseEvent *event,ImageItem *image);
private:
    QPoint BeginPoint,EndPoint;
    void paint(ImageItem *image);
signals:

public slots:
};

#endif // ERASERTOOL_H
