#ifndef TEREMTABLEMODEL_H
#define TEREMTABLEMODEL_H

#include <QSqlRelationalTableModel>

class TeremTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    TeremTableModel(QObject* parent = 0);


private:
    void setupModel(); // adatok betöltése

};

#endif // TEREMTABLEMODEL_H
