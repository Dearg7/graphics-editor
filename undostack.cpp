#include "undostack.h"

UndoStack::UndoStack(ImageItem *img,QObject *parent):QObject(parent)

{
   UImageItem = img;
   curr = 0;
   max = 30;
   numRedo = 0;

}


void UndoStack::pushUndoStack(QImage img)
{

    if (curr == 0)
          emit canUndo(true);


    if (curr < max)
    {
        stack.push_back(img);
        curr++;
    }else
    {
        stack.removeFirst();
        stack.push_back(img);
    }
    while (!redoStack.isEmpty())
    {
        redoStack.removeLast();

    }
    numRedo = 0;
    emit canRedo(false);
}

void UndoStack::clearAll()
{
    while (!redoStack.isEmpty())
    {
        redoStack.removeLast();
    }
    emit canRedo(false);
    while (!stack.isEmpty())
    {
        stack.removeLast();

    }
    curr = 0;
    numRedo = 0;
    //stack.push_back(*(UImageItem->getImage()));
    emit canUndo(false);
    emit canRedo(false);
}

void UndoStack::undo()
{
    if (numRedo == 0)
        emit canRedo(true);
    UImageItem->clearSelection();
    redoStack.push_back(*(UImageItem->getImage()));
    UImageItem->setImage(stack.takeLast());
    UImageItem->update();
    numRedo++;
    curr--;
    if (curr == 0)
        emit canUndo(false);
}

void UndoStack::redo()
{
    if (curr == 0)
        emit canUndo(true);
    stack.push_back(*(UImageItem->getImage()));
    UImageItem->setImage(redoStack.takeLast());
    UImageItem->update();
    numRedo--;
    curr++;
    if (numRedo == 0)
        emit canRedo(false);

}
