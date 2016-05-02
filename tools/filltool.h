#ifndef FILLTOOL_H
#define FILLTOOL_H

#include <QObject>
#include "imageitem.h"

class FillTool : public QObject
{
    Q_OBJECT
public:
    explicit FillTool(QObject *parent = 0);
     ~FillTool(){}


    void mousePressEvent(QMouseEvent *event,ImageItem *image);

private:
    QPoint CurrentPoint;

    void paint(ImageItem *imagr,bool check);
signals:

public slots:
};

#endif // FILLTOOL_H
