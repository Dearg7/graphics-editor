#include "penciltool.h"
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <imageitem.h>


PencilTool::PencilTool(QObject *parent) : QObject(parent)
{


}

void PencilTool::mousePressEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->button() == Qt::LeftButton))
    {
        BeginPoint = EndPoint = event->pos();
        paint(image,image->getColor1());
    }
    if ((event->button() == Qt::RightButton))
    {
        BeginPoint = EndPoint = event->pos();
        paint(image,image->getColor2());
    }


}

void PencilTool::mouseMoveEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->buttons() == Qt::LeftButton))
    {
        EndPoint = event->pos();
        paint(image,image->getColor1());
        BeginPoint = event->pos();

    }
    if ((event->buttons() == Qt::RightButton))
    {
        EndPoint = event->pos();
        paint(image,image->getColor2());
        BeginPoint = event->pos();

    }

}

void PencilTool::mouseReleaseEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->button() == Qt::LeftButton))
    {
        EndPoint = event->pos();
        paint(image,image->getColor1());
    }
    if ((event->button() == Qt::RightButton))
    {
        EndPoint = event->pos();
        paint(image,image->getColor2());
    }

}

void PencilTool::paint(ImageItem *image,QColor Clr)
{
    QPainter painter(image->getImage());
    painter.setPen(QPen(Clr,image->getSize(),Qt::SolidLine,Qt::RoundCap));
    if (EndPoint == BeginPoint )
        painter.drawPoint(BeginPoint);
    if (EndPoint != BeginPoint)
        painter.drawLine(BeginPoint,EndPoint);
    painter.end();
    image->update();
}
