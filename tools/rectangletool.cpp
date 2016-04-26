#include "rectangletool.h"
#include <QPen>
#include <QPainter>

RectangleTool::RectangleTool(QObject *parent) : QObject(parent)
{

}

void RectangleTool::mousePressEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->button() == Qt::LeftButton || event->button() == Qt::RightButton))
        {
            imageCopy = *(image->getImage());
            BeginPoint = EndPoint = event->pos();

        }
}

void RectangleTool::mouseMoveEvent(QMouseEvent *event, ImageItem *image)
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

void RectangleTool::mouseReleaseEvent(QMouseEvent *event, ImageItem *image)
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

void RectangleTool::paint(ImageItem *image, bool check)
{
    QPainter painter(image->getImage());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(image->getColor1(),image->getSize(),Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));
    if (check)
        painter.setBrush(QBrush(image->getColor2()));
    if (BeginPoint != EndPoint)
    painter.drawRect(QRect(BeginPoint,EndPoint));
    painter.end();
    image->update();
}
