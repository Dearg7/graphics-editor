#include "colorselection.h"
#include <QColorDialog>


ColorSelection::ColorSelection(QColor color,QWidget *parent)
    : QLabel(parent)
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    colorSelection = new QColor(color);
    pixmapSelection = new QPixmap(30,30);
    painterSelection = new QPainter(pixmapSelection);
    painterSelection->begin(pixmapSelection);
    painterSelection->fillRect(0,0,30,30,*colorSelection);
    painterSelection->end();
    setPixmap(*pixmapSelection);
    setFixedHeight(30);
    setFixedWidth(30);

}

ColorSelection::~ColorSelection()
{

    delete pixmapSelection;
    delete colorSelection;
    delete painterSelection;
}

void ColorSelection::setColor(QColor color)
{
    *colorSelection = color;
    painterSelection->begin(pixmapSelection);
    painterSelection->fillRect(0,0,30,30,*colorSelection);
    painterSelection->end();
    setPixmap(*pixmapSelection);
}

void ColorSelection::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QColor color = QColorDialog::getColor(*colorSelection,this);\

       if (color.isValid() == true)
       {
           setColor(color);
           emit changeColor(color);

       }


    }

}

