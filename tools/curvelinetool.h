#ifndef CURVELINETOOL_H
#define CURVELINETOOL_H

#include <QObject>
#include "imageitem.h"

class ImageItem;
class CurveLineTool : public QObject
{
    Q_OBJECT
public:
    explicit CurveLineTool(QObject *parent = 0);
        ~CurveLineTool(){};
    void mousePressEvent(QMouseEvent *event,ImageItem *image);
    void mouseMoveEvent(QMouseEvent *event,ImageItem *image);
    void mouseReleaseEvent(QMouseEvent *event,ImageItem *image);

private:
    QPoint BeginPoint,EndPoint,FirstPoint,SecondPoint;
    QImage imageCopy;
    int amount;
    void paint(ImageItem *image,bool check);

signals:

public slots:
};

#endif // CURVELINETOOL_H
