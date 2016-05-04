#ifndef UNDOSTACK_H
#define UNDOSTACK_H
#include <QList>
#include <QImage>
#include "imageitem.h"
#include <QObject>

class ImageItem;

class UndoStack : public QObject
{
    Q_OBJECT
public:
    UndoStack(ImageItem *img, QObject *parent = 0);

    void pushUndoStack(QImage img);
    void clearAll();

private:
    QList<QImage> stack;
    QList<QImage> redoStack;
    ImageItem *UImageItem;
    int max ;
    int curr ;
    int numRedo;
public slots:
    void undo();
    void redo();
signals:
    void canRedo(bool);
    void canUndo(bool);


};

#endif // UNDOSTACK_H
