#ifndef COLORSELECTION_H
#define COLORSELECTION_H

#include <QLabel>
#include <QWidget>
#include <QColor>


class ColorSelection : public QLabel
{


public:
   explicit ColorSelection(QColor color,QWidget *parent = 0);
    ~ColorSelection();

private:
    QColor *colorSelection;
    QPixmap *pixmapSelection;
    QPainter *painterSelection;

public slots:

    void setColor(QColor color);

 signals:

    void changeColor(const QColor color);


protected:
    void mousePressEvent(QMouseEvent *event);


};

#endif // COLORSELECTION_H
