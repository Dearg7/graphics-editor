#include "imageitem.h"
#include <QPainter>
#include <QPen>
#include <QImage>
#include <QDebug>
#include "tools/penciltool.h"

ImageItem::ImageItem(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(640);
    this->setFixedWidth(800);
    _image = new QImage(800,640,QImage::Format_RGB32);
    _image->fill(Qt::white);
    pen = new PencilTool();
}

ImageItem::~ImageItem()
{

}

QImage *ImageItem::getImage()
{
    return _image;

}

void ImageItem::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.save();

    painter.setBrush(Qt::white);
    painter.setPen(Qt::black);

    painter.drawRect(0,0,800,640);

    painter.drawImage(0,0,*_image);

    painter.restore();


}

void ImageItem::mousePressEvent(QMouseEvent *event)
{

   pen->mousePressEvent(event,this);
}

void ImageItem::mouseMoveEvent(QMouseEvent *event)
{
    pen->mouseMoveEvent(event,this);
    qDebug() << "NIGGA";

}

void ImageItem::mouseReleaseEvent(QMouseEvent *event)
{
    pen->mouseReleaseEvent(event,this);
}

