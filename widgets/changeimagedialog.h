#ifndef CHANGEIMAGEDIALOG_H
#define CHANGEIMAGEDIALOG_H

#include <QWidget>
#include <QDialog>
#include "imageitem.h"

class ImageItem;

class ChangeImageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ChangeImageDialog(int w, int h,ImageItem *image, QWidget *parent = 0);

signals:

public slots:
};

#endif // CHANGEIMAGEDIALOG_H
