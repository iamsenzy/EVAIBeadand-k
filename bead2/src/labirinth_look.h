#ifndef LABIRINTH_LOOK_H
#define LABIRINTH_LOOK_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include "gridpushbutton.h"
#include "labirinth_modell.h"

class Labirinth_Look : public QWidget
{
    Q_OBJECT

public:
    Labirinth_Look(QWidget *parent = 0);
    ~Labirinth_Look();

private slots:
    void new_Game();
    void update();
    void activateButtons();
    void changePosition();
    void End();

private:
    int size;
    Labirinth_Modell* modell;
    QPushButton* _sizeButton;
    QGridLayout* _gridLayout;
    QVBoxLayout* _vBoxLayout;
    QHBoxLayout* _hBoxLayout;
    QVector<GridPushButton*> _buttonGrid;

    QPushButton* _smallGameButton;
    QPushButton* _middleGameButton;
    QPushButton* _largeGameButton;
    QPushButton* _pauseButton;
    QLabel* _messageLabel;
};

#endif // LABIRINTH_LOOK_H
