#include "changedialog.h"
#include <QHBoxLayout>

ChangeDialog::ChangeDialog(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(200,80);
    setWindowTitle(trUtf8("Beállítások"));
    setModal(true); // előugró ablak, rögtön megkapja a fókuszt

    _label = new QLabel(trUtf8("Gombok száma: "));
    _spinBox = new QSpinBox();
    _spinBox->setRange(3,6); // az értékek 1 és 10 közöttiek lehetnek
    _spinBox->setSingleStep(1); // a lépésköz 10

    _okButton = new QPushButton(trUtf8("OK"));
    _okButton->setFixedSize(75, 23); // a gombok mérete rögzített
    _cancelButton = new QPushButton(trUtf8("Mégse"));
    _cancelButton->setFixedSize(75, 23);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept())); // elfogadás állapota
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject())); // elvetés állapota

    QHBoxLayout *upperLayout = new QHBoxLayout();
    upperLayout->addWidget(_label);
    upperLayout->addWidget(_spinBox);

    QHBoxLayout *lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(_okButton);
    lowerLayout->addWidget(_cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);

    setLayout(mainLayout);
}
