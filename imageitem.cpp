#include "imageitem.h"
#include <QPainter>
#include <QPen>
#include <QImage>

#include "tools/penciltool.h"
#include <QFileDialog>
#include <QTextCodec>
#include <QMessageBox>
#include "widgets/changeimagedialog.h"


class ChangeImageDialog;
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
    selection = new SelectionTool();
    QObject::connect(pipette,SIGNAL(changeColor1(QColor)),this,SLOT(setColor1(QColor)));
    QObject::connect(pipette,SIGNAL(changeColor2(QColor)),this,SLOT(setColor2(QColor)));
    color1 = new QColor(Qt::black);
    color2 = new QColor(Qt::white);
    size = 10;
    iZoom = 100;
    imageRect = _image->rect();
    imageSize = _image->size();
    newCurve = false;
    pencilCheck = false;
    eraserCheck = false;
    ellipseCheck = false;
    rectangleCheck = false;
    lineCheck = false;
    curveLineCheck = false;
    fillCheck = false;
    pipetteCheck = false;
    selectionCheck  = false;
    UStack = new UndoStack(this);

    //Create slider
    slider = new QSlider(Qt::Horizontal);
    spinBox = new QSpinBox();
    QObject::connect(spinBox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    QObject::connect(slider,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));
    spinBox->setMaximum(100);
    spinBox->setMinimum(1);
    spinBox->setValue(10);
    slider->setMaximum(100);
    slider->setMinimum(1);
    slider->setValue(10);
    QObject::connect(slider,SIGNAL(valueChanged(int)),this,SLOT(setSize(int)));

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

SelectionTool *ImageItem::getSelection()
{
    return selection;

}

double ImageItem::getZoom()
{
    return iZoom/100;

}

QSlider *ImageItem::getSlider()
{
    return slider;
}

QSpinBox *ImageItem::getSpinBox()
{
    return spinBox;

}

void ImageItem::zooming()
{


    *_image = _image->transformed(QTransform::fromScale(iZoom/prevZoom,(iZoom/prevZoom)));
    setFixedSize(_image->size());
    clearSelection();
    update();

}

void ImageItem::paintEvent(QPaintEvent *)
{
    imageRect = QRect(QPoint(0,0),_image->size()*(iZoom/100));
    setFixedSize(imageSize*(iZoom/100));
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();


    painter.setBrush(Qt::white);
    painter.setPen(Qt::black);
    painter.drawRect(imageRect);

    painter.drawImage(imageRect,*_image);

    painter.restore();


}

void ImageItem::mousePressEvent(QMouseEvent *event)
{




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

     fill->mousePressEvent(event,this);

  }
  if (selectionCheck)
      selection->mousePressEvent(event,this);
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
       qDebug() << event->pos();
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
     if (selectionCheck)
         selection->mouseMoveEvent(event,this);


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
      if (selectionCheck)
          selection->mouseReleaseEvent(event,this);


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

void ImageItem::senseFill(const bool b)
{
    if (b)
    {
        copySize = size;
        size = 0;
        slider->setMinimum(0);
        spinBox->setMinimum(0);
        slider->setValue(size);
        spinBox->setValue(size);

    } else
      {
       slider->setMinimum(1);
       spinBox->setMinimum(1);
       size = copySize;
       slider->setValue(size);
       spinBox->setValue(size);
    }
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
        imageSize = _image->size();

        currentFile = file;
        UStack->clearAll();
        newCurve = true;
        iZoom = 100;

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

void ImageItem::setSelection(const bool b)
{
    selectionCheck = b;
    if (b)
        setMouseTracking(true);
    else
        setMouseTracking(false);
}

void ImageItem::makeCopy()
{
    selection->copyImage(this);
}

void ImageItem::makeCut()
{
    selection->cutImage(this);
}

void ImageItem::makePut()
{
    selection->putImage(this);

}

void ImageItem::clearSelection()
{
    selection->clearSelection(this);

}

void ImageItem::zoomPlus()
{
    if (iZoom == 500)
           return;
     prevZoom = iZoom;
    if (iZoom < 100)
        iZoom += 25; else
        {
                if (iZoom < 300)
                    iZoom += 50; else
                        iZoom += 100;
        }
    //zooming();
    update();

}

void ImageItem::zoomMinus()
{
    qDebug() << "Nigga";

    if (iZoom == 25)
           return;
     prevZoom = iZoom;
    if (iZoom <= 100)
        iZoom -= 25; else
        {
                if (iZoom <= 300)
                    iZoom -= 50; else
                        iZoom -= 100;
        }

    qDebug() << "Nigga2";


    //zooming();
    update();
}

void ImageItem::change()
{
    cWidth = imageSize.width();
    cHeight = imageSize.height();
    ChangeImageDialog *dialog = new ChangeImageDialog(imageSize.width(),imageSize.height(),this);
    dialog->exec();
    delete dialog;

}

void ImageItem::changeWidth(int w)
{
    cWidth = w;
}

void ImageItem::changeHeight(int h)
{
    cHeight = h;

}

void ImageItem::changeAccept()
{
    UStack->pushUndoStack(*_image);
    *_image = _image->scaled(cWidth,cHeight);
    imageSize = _image->size();
    clearSelection();
}

