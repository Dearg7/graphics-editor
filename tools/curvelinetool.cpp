#include "curvelinetool.h"
#include <QPen>
#include <QPainter>
CurveLineTool::CurveLineTool(QObject *parent) : QObject(parent)
{
    amount = 0;
}

void CurveLineTool::mousePressEvent(QMouseEvent *event, ImageItem *image)
{
     if (image->getNewCurve())
     {
         image->setNewCurve(false);
         amount = 0;
     }
     if ((event->button() == Qt::LeftButton || event->button() == Qt::RightButton))
     {
         switch (amount)
         {
             case 0:
                 imageCopy = *(image->getImage());
                 EndPoint = BeginPoint = FirstPoint = SecondPoint = event->pos();
                 amount ++;
                 image->getUndoStack()->pushUndoStack(imageCopy);
             break;
             case 1:
                 FirstPoint = SecondPoint = event->pos();
                 amount ++;
             break;
             case 2:
                 SecondPoint = event->pos();
                 amount = 0;
             break;
          }



     }
}

void CurveLineTool::mouseMoveEvent(QMouseEvent *event, ImageItem *image)
{
     if ((event->buttons() == Qt::LeftButton || event->buttons() == Qt::RightButton))
     {
         switch(amount)
         {
         case 1:
             EndPoint = event->pos();
             break;
         case 2:
             FirstPoint = SecondPoint = event->pos();
             break;
         case 0:
             SecondPoint = event->pos();
             break;
         }

         image->setImage(imageCopy);
         if (event->buttons() == Qt::LeftButton)
             paint(image,false);
         if (event->buttons() == Qt::RightButton)
             paint(image,true);

     }
}

void CurveLineTool::mouseReleaseEvent(QMouseEvent *event, ImageItem *image)
{
    if ((event->button() == Qt::LeftButton))
    {
        image->setImage(imageCopy);
        paint(image,false);
    }
    if ((event->button() == Qt::RightButton))
    {
        image->setImage(imageCopy);
        paint(image,true);
    }

}

void CurveLineTool::paint(ImageItem *image, bool check)
{
    QPainter painter(image->getImage());
    QPainterPath path;
    double z = image->getZoom();
    path.moveTo(BeginPoint/z);
    path.cubicTo(FirstPoint/z,SecondPoint/z,EndPoint/z);
    if (check)
    {
        painter.setPen(QPen(image->getColor2(),image->getSize(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    } else

    {
        painter.setPen(QPen(image->getColor1(),image->getSize(),Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    }
    painter.strokePath(path,painter.pen());
    painter.end();
    image->update();
}
