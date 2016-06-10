#include "erasertool.h"
#include <QPen>
#include <QPainter>

EraserTool::EraserTool(QObject *parent) : QObject(parent)
{

}

void EraserTool::mousePressEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->button() == Qt::LeftButton || event->button() == Qt::RightButton))
    {
        BeginPoint = EndPoint = event->pos();
        paint(image);
    }


}

void EraserTool::mouseMoveEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->buttons() == Qt::LeftButton || event->buttons() == Qt::RightButton))
    {
        EndPoint = event->pos();
        paint(image);
        BeginPoint = event->pos();

    }

}

void EraserTool::mouseReleaseEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->button() == Qt::LeftButton || event->button() == Qt::RightButton))
    {
        EndPoint = event->pos();
        paint(image);
    }
}

void EraserTool::paint(ImageItem *image)
{
    QPainter painter(image->getImage());
    double z = image->getZoom();
    painter.setPen(QPen(Qt::white,image->getSize(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    if (EndPoint == BeginPoint )
        painter.drawPoint(BeginPoint/z);
    if (EndPoint != BeginPoint)
        painter.drawLine(BeginPoint/z,EndPoint/z);
    painter.end();
    image->update();
}
