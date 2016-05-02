#include "filltool.h"

FillTool::FillTool(QObject *parent) : QObject(parent)
{

}

void FillTool::mousePressEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->button() == Qt::LeftButton))
    {
        CurrentPoint = event->pos();
        paint(image,false);
    }
    if ((event->button() == Qt::RightButton))
    {
        CurrentPoint = event->pos();
        paint(image,true);
    }

}

void FillTool::paint(ImageItem *image, bool check)
{
    QList<QPoint> list;
    list.push_back(CurrentPoint);
    QPoint point;
    QColor color = image->getImage()->pixelColor(CurrentPoint);

    QImage *img = image->getImage();
    QColor newColor;
    if (check)
        newColor = image->getColor2();
    else
        newColor = image->getColor1();
    if (newColor == color)
            return;
    img->setPixelColor(CurrentPoint,newColor);
    while(!list.isEmpty())
    {
      point = list.takeFirst();

      if (point.x() + 1 < img->width())
      {
          point.setX(point.x() + 1);
         if ((img->pixelColor(point) == color))
         {
                img->setPixelColor(point,newColor);
                list.push_back(point);
         }
         point.setX(point.x() - 1);
      }
      if (point.x() - 1 > 0)
      {
          point.setX(point.x() - 1);
         if ((img->pixelColor(point) == color))
         {
                img->setPixelColor(point,newColor);
                list.push_back(point);
               }
         point.setX(point.x() + 1);
      }
      if (point.y() + 1 < img->height())
      {
          point.setY(point.y() + 1);
         if ((img->pixelColor(point) == color))
         {
                img->setPixelColor(point,newColor);
                list.push_back(point);
          }
         point.setY(point.y() - 1);
      }
      if (point.y() - 1 > 0)
      {
          point.setY(point.y() - 1);
         if ((img->pixelColor(point) == color))
         {
                img->setPixelColor(point,newColor);
                list.push_back(point);
         }
         point.setY(point.y() + 1);
      }


    }

    image->update();
}
