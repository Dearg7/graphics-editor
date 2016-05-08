#include "linetool.h"
#include <QPen>
#include <QPainter>

LineTool::LineTool(QObject *parent) : QObject(parent)
{

}

void LineTool::mousePressEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->button() == Qt::LeftButton || event->button() == Qt::RightButton))
    {
        imageCopy = *(image->getImage());
        BeginPoint = EndPoint = event->pos();

    }
}

void LineTool::mouseMoveEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->buttons() == Qt::LeftButton))
    {

        image->setImage(imageCopy);
        EndPoint = event->pos();
        paint(image,false);


    }
    if ((event->buttons() == Qt::RightButton))
    {
        image->setImage(imageCopy);
        EndPoint = event->pos();
        paint(image,true);


    }

}

void LineTool::mouseReleaseEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->button() == Qt::LeftButton))
    {
        image->setImage(imageCopy);
        EndPoint = event->pos();
        paint(image,false);
    }
    if ((event->button() == Qt::RightButton))
    {
        image->setImage(imageCopy);
        EndPoint = event->pos();
        paint(image,true);
    }

}

void LineTool::paint(ImageItem *image, bool check)
{
    QPainter painter(image->getImage());
    double z = image->getZoom();
    if (check)
    {
        painter.setPen(QPen(image->getColor2(),image->getSize(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    } else
    {
        painter.setPen(QPen(image->getColor1(),image->getSize(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    }


    if (BeginPoint == EndPoint)
    {
        painter.drawPoint(BeginPoint/z);
    } else
    {
        painter.drawLine(BeginPoint/z,EndPoint/z);
    }
    painter.end();
    image->update();

}
