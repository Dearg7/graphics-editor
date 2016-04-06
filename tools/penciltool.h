#ifndef PENCILTOOL_H
#define PENCILTOOL_H

#include <QObject>
#include <QMouseEvent>
#include <QImage>
#include <imageitem.h>

QT_BEGIN_NAMESPACE
class ImageItem;
QT_END_NAMESPACE



class PencilTool : public QObject
{
    Q_OBJECT
public:
    explicit PencilTool(QObject *parent = 0);
    ~PencilTool(){};

    void mousePressEvent(QMouseEvent *event,ImageItem *image);
    void mouseMoveEvent(QMouseEvent *event,ImageItem *image);
    void mouseReleaseEvent(QMouseEvent *event,ImageItem *image);

private:
    QPoint BeginPoint,EndPoint;
    void paint(ImageItem *image);

signals:


public slots:
};

#endif // PENCILTOOL_H
