#ifndef SELECTIONTOOL_H
#define SELECTIONTOOL_H

#include <QObject>
#include "imageitem.h"

class ImageItem;

class SelectionTool : public QObject
{
    Q_OBJECT
public:
    explicit SelectionTool(QObject *parent = 0);
        ~SelectionTool(){};

    void mousePressEvent(QMouseEvent *event,ImageItem *image);
    void mouseMoveEvent(QMouseEvent *event,ImageItem *image);
    void mouseReleaseEvent(QMouseEvent *event,ImageItem *image);

protected:
    void drawBorder(ImageItem *image);
    void updateCursor(QMouseEvent *event,ImageItem *image);
    void clearSelection(ImageItem *image);
    void paintBackground(ImageItem *image);
    void paint(ImageItem *image);



    bool selected,canPaint,moving,changing,imageSelected,resizing;
    QImage ImageCopy,ImageSelection;
    QPoint Point1,Point2,movePoint;
signals:

public slots:
};

#endif // SELECTIONTOOL_H
