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
    eraser = new EraserTool();
    ellipse = new EllipseTool();
    rectangle = new RectangleTool();
    curveLine = new CurveLineTool();
    fill = new FillTool();
    line = new LineTool();
    pipette = new PipetteTool();
    QObject::connect(pipette,SIGNAL(changeColor1(QColor)),this,SLOT(setColor1(QColor)));
    QObject::connect(pipette,SIGNAL(changeColor2(QColor)),this,SLOT(setColor2(QColor)));
    color1 = new QColor(Qt::black);
    color2 = new QColor(Qt::white);
    size = 10;
    imageRect = _image->rect();
    newCurve = false;
    pencilCheck = false;
    eraserCheck = false;
    ellipseCheck = false;
    rectangleCheck = false;
    lineCheck = false;
    curveLineCheck = false;
    fillCheck = false;
    pipetteCheck = false;
    UStack = new UndoStack(this);
}

ImageItem::~ImageItem()
{

}

QImage *ImageItem::getImage()
{
    return _image;

}

bool ImageItem::getNewCurve()
{
    return newCurve;

}

void ImageItem::setImage(QImage img)
{
    *(_image) = img;

}

QColor ImageItem::getColor1()
{
    return *color1;

}

QColor ImageItem::getColor2()
{
    return *color2;

}

PipetteTool *ImageItem::getPipette()
{
    return pipette;

}

int ImageItem::getSize()
{
    return size;

}

UndoStack *ImageItem::getUndoStack()
{
    return UStack;

}

void ImageItem::paintEvent(QPaintEvent *)
{
    imageRect = _image->rect();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();


    painter.setBrush(Qt::white);
    painter.setPen(Qt::black);
    painter.drawRect(imageRect);

    painter.drawPixmap(0,0,_image->width(),_image->height(),QPixmap::fromImage(*_image));

    painter.restore();


}

void ImageItem::mousePressEvent(QMouseEvent *event)
{



   qDebug() << "Nigga";

  if (pencilCheck)
  {
      UStack->pushUndoStack(*(_image));
      pen->mousePressEvent(event,this);

   }
  if (eraserCheck)
  {
       UStack->pushUndoStack(*(_image));
      eraser->mousePressEvent(event,this);

  }
  if (ellipseCheck)
  {
      UStack->pushUndoStack(*(_image));
      ellipse->mousePressEvent(event,this);

  }
  if (rectangleCheck)
   {
      UStack->pushUndoStack(*(_image));
      rectangle->mousePressEvent(event,this);

  }
  if (lineCheck)
  {
      UStack->pushUndoStack(*(_image));
      line->mousePressEvent(event,this);

  }
  if (fillCheck)
  {
      UStack->pushUndoStack(*(_image));
     fill->mousePressEvent(event,this);

  }
  if (curveLineCheck)
      curveLine->mousePressEvent(event,this);
  if (pipetteCheck)
  {
       pipette->mousePressEvent(event,this);
       qDebug() << "Nigga Pipette";
      }

}

void ImageItem::mouseMoveEvent(QMouseEvent *event)
{
     if (pencilCheck)
            pen->mouseMoveEvent(event,this);
     if (eraserCheck)
         eraser->mouseMoveEvent(event,this);
     if (ellipseCheck)
         ellipse->mouseMoveEvent(event,this);
     if (rectangleCheck)
         rectangle->mouseMoveEvent(event,this);
     if (lineCheck)
         line->mouseMoveEvent(event,this);
     if (curveLineCheck)
         curveLine->mouseMoveEvent(event,this);


}

void ImageItem::mouseReleaseEvent(QMouseEvent *event)
{
      if (pencilCheck)
      {
            pen->mouseReleaseEvent(event,this);
      }
      if (eraserCheck)
      {
          eraser->mouseReleaseEvent(event,this);

      }
      if (ellipseCheck)
      {
          ellipse->mouseReleaseEvent(event,this);

      }
      if (rectangleCheck)
      {
          rectangle->mouseReleaseEvent(event,this);

       }
      if (lineCheck)
      {
          line->mouseReleaseEvent(event,this);

      }
      if (curveLineCheck)
          curveLine->mouseReleaseEvent(event,this);


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
        UStack->clearAll();
        newCurve = true;

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
    {
        currentFile = file;
        UStack->clearAll();
        newCurve = true;
    }
    else
        QMessageBox::warning(this,tr("Ошибка сохранение файла"),tr("Файл не сохранён"));
}

void ImageItem::save()
{
    if (currentFile.isEmpty())
        return saveAs();
    qDebug() << currentFile;
    if (!_image->save(currentFile))
        QMessageBox::warning(this,tr("Ошибка сохранение файла"),tr("Файл не сохранён"));
        else
    {

            UStack->clearAll();
            newCurve = true;
    }



}

void ImageItem::setNewCurve(const bool b)
{
    newCurve = b;

}

void ImageItem::setPencil(const bool b)
{
    pencilCheck = b;
}

void ImageItem::setEraser(const bool b)
{
    eraserCheck = b;
}

void ImageItem::setEllipse(const bool b)
{
    ellipseCheck = b;
}

void ImageItem::setRectangle(const bool b)
{
    rectangleCheck = b;
}

void ImageItem::setLine(const bool b)
{
    lineCheck = b;
}

void ImageItem::setCurveLine(const bool b)
{
    curveLineCheck = b;
}

void ImageItem::setFill(const bool b)
{
    fillCheck = b;
}

void ImageItem::setPipette(const bool b)
{
    pipetteCheck = b;
}

