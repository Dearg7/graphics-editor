#include "selectiontool.h"
#include <QClipboard>
#include <QApplication>


SelectionTool::SelectionTool(QObject *parent) : QObject(parent)
{
    canPaint = selected = moving = imageSelected = resizing = checkUndo = false;

}

void SelectionTool::mousePressEvent(QMouseEvent *event, ImageItem *image)
{
    if (selected && (event->button() == Qt::LeftButton))
    {
        image->setImage(ImageCopy);
        paint(image);
        if (event->pos().x() > Point1.x() &&
            event->pos().x() < Point2.x() &&
            event->pos().y() > Point1.y() &&
            event->pos().y() < Point2.y())
        {
           if (!checkUndo)
           {
               checkUndo = true;
               image->getUndoStack()->pushUndoStack(*(image->getImage()));

           }

           if (!imageSelected)
           {
               paintBackground(image);
               imageSelected = true;
           }


           moving = true;
           movePoint =  event->pos();
           drawBorder(image);
           return;
        } else if (event->pos().x() >= Point2.x() &&
                   event->pos().x() <= Point2.x() + 5 &&
                   event->pos().y() >= Point2.y() &&
                   event->pos().y() <= Point2.y() + 5)
        {
            if (!checkUndo)
            {
                checkUndo = true;
                image->getUndoStack()->pushUndoStack(*(image->getImage()));

            }
            if (!imageSelected)
            {
                paintBackground(image);

            }
            resizing = true;

            drawBorder(image);
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

            Point2 = Point2 + (event->pos() - movePoint);
            Point1 = Point1 + (event->pos() - movePoint);

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
           emit canCopy(true);

        }
    }
}

void SelectionTool::copyImage(ImageItem *image)
{

    qDebug() <<"Copy Nigga";
    if (selected)
    {

        qDebug() << "Selected Nigga";
        QClipboard *clipboard = QApplication::clipboard();
        image->setImage(ImageCopy);
        paint(image);

        if (imageSelected)
        {
            clipboard->setImage(ImageSelection);
        }else
        {
            clipboard->setImage(image->getImage()->copy(Point1.x(),Point1.y(),Point2.x()-Point1.x() + 1,Point2.y()-Point1.y() + 1));
        }
        emit canPut(true);
        emit canCopy(false);

    }

}

void SelectionTool::cutImage(ImageItem *image)
{
    if (selected)
    {
        copyImage(image);
        image->setImage(ImageCopy);
        paint(image);
        image->getUndoStack()->pushUndoStack(*(image->getImage()));
        image->setImage(ImageCopy);
        if(!imageSelected)
        {
            paintBackground(image);

        }
        canPaint = selected = moving = imageSelected = resizing =  false;
        image->update();



    }


}

void SelectionTool::putImage(ImageItem *image)
{
    QClipboard *clipboard = QApplication::clipboard();
    if (selected)
    {
        image->setImage(ImageCopy);
        paint(image);

    }

    QImage put = clipboard->image();
    if (!put.isNull())
    {
       image->getUndoStack()->pushUndoStack(*(image->getImage()));
       ImageSelection = put;
       ImageCopy = *(image->getImage());
       Point1 = QPoint(0,0);
       Point2 = QPoint(QPoint(put.width(),put.height()) - QPoint(1,1));
       selected = imageSelected = checkUndo = true;
       paint(image);

       drawBorder(image);

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
         canPaint = selected = moving = imageSelected = resizing = checkUndo =  false;
         image->update();

         emit canCopy(false);

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
