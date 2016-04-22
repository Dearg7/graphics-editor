#include "imageitem.h"
#include <QPainter>
#include <QPen>
#include <QImage>
#include <QDebug>
#include "tools/penciltool.h"
#include <QFileDialog>
#include <QTextCodec>
#include <QMessageBox>


ImageItem::ImageItem(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(640);
    this->setFixedWidth(800);
    _image = new QImage(800,640,QImage::Format_ARGB32_Premultiplied);
    _image->fill(Qt::white);
    pen = new PencilTool();
    color1 = new QColor(Qt::black);
    color2 = new QColor(Qt::white);
    size = 10;
    imageRect = _image->rect();
}

ImageItem::~ImageItem()
{

}

QImage *ImageItem::getImage()
{
    return _image;

}

QColor ImageItem::getColor1()
{
    return *color1;

}

QColor ImageItem::getColor2()
{
    return *color2;

}

int ImageItem::getSize()
{
    return size;

}

void ImageItem::paintEvent(QPaintEvent *)
{
    imageRect = _image->rect();

    QPainter painter(this);
    painter.save();

    painter.setBrush(Qt::white);
    painter.setPen(Qt::black);

    painter.drawRect(imageRect);

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


}

void ImageItem::mouseReleaseEvent(QMouseEvent *event)
{
    pen->mouseReleaseEvent(event,this);
}

void ImageItem::setColor1(const QColor _color)
{
    *color1 = _color;
}

void ImageItem::setColor2(const QColor _color)
{
    *color2 = _color;
}

void ImageItem::setSize(const int _size)
{
    size = _size;
}

void ImageItem::open()
{
    QString file = QFileDialog::getOpenFileName(this,"Открываем файл","","Images (*.png *.xpm *.jpg *.gif)");
    if (file.isEmpty())
        return;
    if (_image->load(file))
    {
        *_image = _image->convertToFormat(QImage::Format_ARGB32_Premultiplied);
        setFixedSize(_image->size());
        currentFile = file;

    } else
    {
        QMessageBox::warning(this,tr("Ошибка открытия файла"),tr("Не можем открыть файл %1").arg(file));
    }
    this->update();
}

void ImageItem::saveAs()
{
   QString file =  QFileDialog::getSaveFileName(this,"Сохраняем файл","", "(*.jpg);;(*.png);;(*.xpm)");
   qDebug()<< file;

    if(_image->save(file))
        currentFile = file;
    else
        QMessageBox::warning(this,tr("Ошибка сохранение файла"),tr("Файл не сохранён"));
}

void ImageItem::save()
{
    if (currentFile.isEmpty())
        return saveAs();
    if (!_image->save(currentFile))
        QMessageBox::warning(this,tr("Ошибка сохранение файла"),tr("Файл не сохранён"));


}

