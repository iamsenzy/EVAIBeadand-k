#ifndef TILI_TOLI_H
#define TILI_TOLI_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "gridsizedialog.h"
#include "gridpushbutton.h"
#include "enddialog.h"

class Tili_Toli : public QWidget
{
    Q_OBJECT

public:
    Tili_Toli(QWidget *parent = 0);
    ~Tili_Toli();
    int search(Coordinate coordinate);
    void activateButtons();
    void disableButtons();
    bool end();

private slots:
    void setNumber();
    void resizeGrid();

private:

    int lepesek=0;
    Coordinate ures;
    endDialog* _endDialog;
    GridSizeDialog* _gridSizeDialog;
    QPushButton *_sizeButton;
    QGridLayout* _gridLayout;
    QVBoxLayout *_vBoxLayout;
    QVector<GridPushButton*> _buttonGrid;
};

#endif // TILI_TOLI_H
