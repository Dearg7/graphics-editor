#ifndef COLORSELECTION_H
#define COLORSELECTION_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include <QPainter>
#include <QColor>

class ColorSelection : public QLabel
{
    Q_OBJECT
public:
    explicit ColorSelection(QColor color, QWidget *parent = 0);

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
