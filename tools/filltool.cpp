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

bool Equil(QRgb c1, QRgb c2,double m)
{

 QColor a = QColor::fromRgb(c1);
  QColor b = QColor::fromRgb(c2);
  return sqrt(pow(a.red() - b.red(),2) + pow(a.green() - b.green(),2) + pow(a.blue() - b.blue(),2)) <= m;



}

void FillTool::paint(ImageItem *image, bool check)
{
       QList<int> listX;
       QList<int> listY;
       double z = image->getZoom();
       double sense = ((sqrt(3)*255)/100)*image->getSize();
       int x = CurrentPoint.x() / z , y = CurrentPoint.y() / z;
       bool *used = new bool[10000000];

       QImage *img = image->getImage();
       int imgHeight = img->height();
       int imgWidth = img->width();
       listX.push_back(x);
       listY.push_back(y);
       QRgb color = image->getImage()->pixel(x,y);
       used[x + (y)*(imgWidth + 2)] = true;

       QRgb newColor;
       if (check)
           newColor = image->getColor2().rgb();
       else
           newColor = image->getColor1().rgb();
       if (newColor == color)
               return;
       image->getUndoStack()->pushUndoStack(*img);
       img->setPixel(x,y,newColor);
       while (!listX.isEmpty())
       {

           x = listX.takeFirst();
           y = listY.takeFirst();

           if (x + 1 < imgWidth)
           {
               if (!used[x + 1 + (y)*(imgWidth + 2)])
               if (Equil(img->pixel(x + 1,y),color,sense))
               {
                   listX.push_back(x + 1);
                   listY.push_back(y);
                   img->setPixel(x + 1,y,newColor);
                   used[x + 1 + (y)*(imgWidth + 2)] = true;
               }
           }
           if (x - 1 > 0)
           {
               if (!used[x - 1 + (y)*(imgWidth + 2)])
               if (Equil(img->pixel(x - 1,y),color,sense))
               {
                   listX.push_back(x - 1);
                   listY.push_back(y);
                   img->setPixel(x - 1,y,newColor);
                   used[x - 1 + (y)*(imgWidth + 2)] = true;
               }
           }
           if (y + 1 < imgHeight)
           {
               if (!used[x + (y + 1)*(imgWidth + 2)])
               if (Equil(img->pixel(x,y + 1),color,sense))
               {
                   listX.push_back(x);
                   listY.push_back(y + 1);
                   img->setPixel(x,y + 1,newColor);
                   used[x + (y + 1)*(imgWidth + 2)] = true;
               }
           }
           if (y - 1 > 0)
           {
               if (!used[x + (y - 1)*(imgWidth + 2)])
               if (Equil(img->pixel(x,y - 1),color,sense))
               {
                   listX.push_back(x);
                   listY.push_back(y - 1);
                   img->setPixel(x,y - 1,newColor);
                   used[x + (y - 1)*(imgWidth + 2)] = true;
               }
           }

       }

    delete used;

    image->update();
}
