#include "pipettetool.h"

PipetteTool::PipetteTool(QObject *parent) : QObject(parent)
{

}

void PipetteTool::mousePressEvent(QMouseEvent *event, ImageItem *image)
{
    if ((image->getImage()->width() > event->x())&&(event->x() >= 0) && (image->getImage()->height() > event->y())&&(event->y() >= 0))
    {
    QColor color = image->getImage()->pixelColor(event->pos());
    if ((event->button() == Qt::LeftButton))
    {
        emit changeColor1(color);
    }
    if ((event->button() == Qt::RightButton))
    {
        emit changeColor2(color);
    }
    }

}
