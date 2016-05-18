#include "changeimagedialog.h"
#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QBoxLayout>
ChangeImageDialog::ChangeImageDialog(int w, int h, ImageItem *image, QWidget *parent) : QDialog(parent)
{


    QLabel *LWidth = new QLabel(tr("Ширина"));
    QLabel *LHeight = new QLabel(tr("Высота"));
    QSpinBox *SPWidth = new QSpinBox();
    SPWidth->setRange(1,3000);
    SPWidth->setValue(w);
    QObject::connect(SPWidth,SIGNAL(valueChanged(int)),image,SLOT(changeWidth(int)));
    QSpinBox *SPHeight = new QSpinBox();
    SPHeight->setRange(1,3000);
    SPHeight->setValue(h);
    QObject::connect(SPHeight,SIGNAL(valueChanged(int)),image,SLOT(changeHeight(int)));
    QDialogButtonBox *DBB = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QObject::connect(DBB,SIGNAL(accepted()),this,SLOT(accept()));
    QObject::connect(DBB,SIGNAL(accepted()),image,SLOT(changeAccept()));
    QObject::connect(DBB,SIGNAL(rejected()),this,SLOT(close()));
    QGridLayout *layout = new QGridLayout();

    layout->addWidget(LWidth,0,0);
    layout->addWidget(SPWidth,0,1);
    layout->addWidget(LHeight,1,0);
    layout->addWidget(SPHeight,1,1);
    QVBoxLayout *HLayout = new QVBoxLayout();
    HLayout->addLayout(layout);
    HLayout->addWidget(DBB);
    setLayout(HLayout);







}
