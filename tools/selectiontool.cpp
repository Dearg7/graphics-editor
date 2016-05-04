#include "selectiontool.h"


SelectionTool::SelectionTool(QObject *parent) : QObject(parent)
{
    canPaint = selected = moving = imageSelected = resizing =  false;

}

void SelectionTool::mousePressEvent(QMouseEvent *event, ImageItem *image)
{
    if (selected && (event->button() == Qt::LeftButton))
    {
        image->setImage(ImageCopy);
        paint(image);
        drawBorder(image);
        if (event->pos().x() > Point1.x() &&
            event->pos().x() < Point2.x() &&
            event->pos().y() > Point1.y() &&
            event->pos().y() < Point2.y())
        {
           if (!imageSelected)
           {
               paintBackground(image);
               imageSelected = true;
           }

           moving = true;
           movePoint =  event->pos();
           return;
        } else if (event->pos().x() >= Point2.x() &&
                   event->pos().x() <= Point2.x() + 5 &&
                   event->pos().y() >= Point2.y() &&
                   event->pos().y() <= Point2.y() + 5)
        {
            if (!imageSelected)
            {
                paintBackground(image);

            }
            resizing = true;

            return;
        }else

        {
            clearSelection(image);
        }
    }
    if (event->button() == Qt::LeftButton)
    {
        Point1 = Point2 = event->pos();
        ImageCopy = *(image->getImage());
        canPaint = true;

    }
}

void SelectionTool::mouseMoveEvent(QMouseEvent *event, ImageItem *image)
{

    if (selected)
    {
        if (moving)
         {
            qDebug() << Point1 << Point2;
            qDebug() << "Selected Nigga";
            Point2 = Point2 + (event->pos() - movePoint);
            Point1 = Point1 + (event->pos() - movePoint);
            qDebug() << Point1 << Point2;
            movePoint = event->pos();
            image->setImage(ImageCopy);
             paint(image);
            drawBorder(image);

            canPaint = false;

        } else if (resizing)
        {
            Point2 = event->pos();
            image->setImage(ImageCopy);
            paint(image);
            drawBorder(image);
            canPaint = false;


        }

    }
    if (canPaint)
    {
        Point2 = event->pos();
        image->setImage(ImageCopy);
        drawBorder(image);

    }
    updateCursor(event,image);

}

void SelectionTool::mouseReleaseEvent(QMouseEvent *event, ImageItem *image)
{
    if (Point1.x() < Point2.x() &&
        Point1.y() > Point2.y())
    {
        QPoint p1(Point1.x(),Point2.y());
        QPoint p2(Point2.x(),Point1.y());
        Point1 = p1;
        Point2 = p2;
    } else
    if (Point1.x() > Point2.x() &&
        Point1.y() > Point2.y())
    {
        QPoint p1(Point2.x(),Point2.y());
        QPoint p2(Point1.x(),Point1.y());
        Point1 = p1;
        Point2 = p2;
    } else
    if (Point1.x() > Point2.x() &&
        Point1.y() < Point2.y())
    {
        QPoint p1(Point2.x(),Point1.y());
        QPoint p2(Point1.x(),Point2.y());
        Point1 = p1;
        Point2 = p2;
    }
    if (selected)
    {
        if (moving)
        {
            image->setImage(ImageCopy);
            paint(image);
            drawBorder(image);
            canPaint = false;
            moving = false;

        } else if(resizing)
        {

            image->setImage(ImageCopy);
            paint(image);
            ImageSelection = image->getImage()->copy(Point1.x(),Point1.y(),Point2.x()-Point1.x() + 1,Point2.y()-Point1.y() + 1);
            paint(image);

            drawBorder(image);
            canPaint = false;
            resizing = false;


        }
    }
    if (canPaint)
    {
        if (event->button() == Qt::LeftButton)
        {
           if (Point1 != Point2)
           {
               image->setImage(ImageCopy);

               ImageSelection = image->getImage()->copy(Point1.x(),Point1.y(),Point2.x()-Point1.x() + 1,Point2.y()-Point1.y() + 1);

               drawBorder(image);
               selected = true;
           }

           canPaint = false;

        }
    }
}

void SelectionTool::drawBorder(ImageItem *image)
{
    if (Point1 != Point2)
    {
        QPainter painter(image->getImage());
        painter.setPen(QPen(Qt::blue,1,Qt::DashLine,Qt::RoundCap,Qt::RoundJoin));
        painter.drawRect(QRect(Point1,Point2 - QPoint(1,1)));
        painter.end();
        image->update();
    }
}

void SelectionTool::updateCursor(QMouseEvent *event, ImageItem *image)
{
    if (selected)
        {
            qDebug() << "Selected Nigga";
            if (event->pos().x() > Point1.x() &&
                event->pos().x() < Point2.x() &&
                event->pos().y() > Point1.y() &&
                event->pos().y() < Point2.y())
            {
                image->setCursor(Qt::SizeAllCursor);
            }
            else if (event->pos().x() >= Point2.x() &&
                     event->pos().x() <= Point2.x() + 5 &&
                     event->pos().y() >= Point2.y() &&
                     event->pos().y() <= Point2.y() + 5)
            {
                image->setCursor(Qt::SizeFDiagCursor);
            }
            else
            {
                image->setCursor(Qt::CrossCursor);
            }
        }
        else
        {
            image->setCursor(Qt::CrossCursor);
    }
}

void SelectionTool::clearSelection(ImageItem *image)
{
     if (selected)
     {
         image->setImage(ImageCopy);
         paint(image);
         ImageCopy = *(image->getImage());
         canPaint = selected = moving = imageSelected = resizing =  false;
         image->update();

     }

}



void SelectionTool::paintBackground(ImageItem *image)
{
    QPainter painter(image->getImage());
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.drawRect(QRect(Point1,Point2 - QPoint(1,1)));
    painter.end();
    ImageCopy = *(image->getImage());
    paint(image);
    drawBorder(image);
}

void SelectionTool::paint(ImageItem *image)
{
    if (selected)
    {
        if (Point1 != Point2)
        {
            QPainter painter(image->getImage());
            painter.drawImage(QRect(Point1,Point2),ImageSelection,QRect(0,0,ImageSelection.width(),ImageSelection.height()));
            painter.end();
            image->update();
        }
    }
}
