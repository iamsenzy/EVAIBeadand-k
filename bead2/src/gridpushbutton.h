#ifndef GRIDPUSHBUTTON_H
#define GRIDPUSHBUTTON_H

#include <QPushButton>
#include "coordinate.h"

class GridPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GridPushButton(Coordinate coordinate, QWidget *parent = 0);
    Coordinate coordinate() const { return _coordinate; }

protected:
    Coordinate _coordinate;
};

#endif // GRIDPUSHBUTTON_H
