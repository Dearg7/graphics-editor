#ifndef PIPETTETOOL_H
#define PIPETTETOOL_H

#include <QObject>
#include "imageitem.h"

class ImageItem;
class PipetteTool : public QObject
{
    Q_OBJECT
public:
    explicit PipetteTool(QObject *parent = 0);
        ~PipetteTool(){};

    void mousePressEvent(QMouseEvent *event,ImageItem *image);

signals:

    void changeColor1(const QColor color);
    void changeColor2(const QColor color);

public slots:
};

#endif // PIPETTETOOL_H
