#include "enddialog.h"
#include <QHBoxLayout>

endDialog::endDialog(int lepesek, QWidget *parent)
    :_lepesek(lepesek), QDialog(parent)
{
    setFixedSize(250,100);
    setWindowTitle(trUtf8("Nyertél"));
    setModal(true);
    _label = new QLabel(trUtf8("Lépések száma: "));
    _label2 = new QLabel(QString::number(lepesek));

    _ujButton = new QPushButton(trUtf8("Új játék"));
    _ujButton->setFixedSize(75, 23);
    _exButton = new QPushButton(trUtf8("Kilépes"));
    _exButton->setFixedSize(75, 23);

    connect(_ujButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_exButton, SIGNAL(clicked()), this, SLOT(reject()));

    QHBoxLayout *upperLayout = new QHBoxLayout();
    upperLayout->addWidget(_label);
    upperLayout->addWidget(_label2);

    QHBoxLayout *lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(_ujButton);
    lowerLayout->addWidget(_exButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);

    setLayout(mainLayout);

}
