#ifndef CHANGEDIALOG_H
#define CHANGEDIALOG_H


#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

class ChangeDialog : public QDialog // rács méretét beállító dialógus
{
    Q_OBJECT
public:
    explicit ChangeDialog(QWidget *parent = 0);
    //int gridSize() { return _spinBox->value(); } // gombok számának lekérdezése

private:
    QLabel *_label; // címke
    QSpinBox *_spinBox; // számbeállító
    QPushButton *_okButton;
    QPushButton *_cancelButton;
};
#endif // CHANGEDIALOG_H
