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
    if (event->button() == Qt::LeftButton)
    {
        BeginPoint = EndPoint = event->pos();
        paint(image);
    }

}

void PencilTool::mouseMoveEvent(QMouseEvent *event, ImageItem *image)
{
    if (event->buttons() & Qt::LeftButton)
    {
        EndPoint = event->pos();
        paint(image);
        BeginPoint = event->pos();
        qDebug() << "NIGGA2";
    }
     qDebug() << "NIGGA2";
}

void PencilTool::mouseReleaseEvent(QMouseEvent *event, ImageItem *image)
{
    if (event->button() == Qt::LeftButton)
    {
        EndPoint = event->pos();
        paint(image);
    }

}

void PencilTool::paint(ImageItem *image)
{
    QPainter painter(image->getImage());
    painter.setPen(QPen(Qt::red,10,Qt::SolidLine,Qt::RoundCap));
    if (EndPoint == BeginPoint )
        painter.drawPoint(BeginPoint);
    if (EndPoint != BeginPoint)
        painter.drawLine(BeginPoint,EndPoint);
    painter.end();
    image->update();
}
