#include "pipettetool.h"

PipetteTool::PipetteTool(QObject *parent) : QObject(parent)
{

}

void PipetteTool::mousePressEvent(QMouseEvent *event, ImageItem *image)
{
    double z = image->getZoom();
    if ((image->getImage()->width() > event->x()/z)&&(event->x() >= 0) && (image->getImage()->height() > event->y()/z)&&(event->y() >= 0))
    {
    QColor color = image->getImage()->pixel(event->pos()/z);
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
