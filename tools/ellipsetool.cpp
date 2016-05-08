#include "ellipsetool.h"
#include <QPen>
#include <QPainter>

EllipseTool::EllipseTool(QObject *parent) : QObject(parent)
{

}

void EllipseTool::mousePressEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->button() == Qt::LeftButton || event->button() == Qt::RightButton))
    {
        imageCopy = *(image->getImage());
        BeginPoint = EndPoint = event->pos();

    }
}

void EllipseTool::mouseMoveEvent(QMouseEvent *event, ImageItem *image)
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

void EllipseTool::mouseReleaseEvent(QMouseEvent *event, ImageItem *image)
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

void EllipseTool::paint(ImageItem *image, bool check)
{
    QPainter painter(image->getImage());
    double z = image->getZoom();
    painter.setPen(QPen(image->getColor1(),image->getSize(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    if (check)
        painter.setBrush(QBrush(image->getColor2()));
    if (BeginPoint != EndPoint)
    painter.drawEllipse(QRect(BeginPoint/z,EndPoint/z));
    painter.end();
    image->update();
}

