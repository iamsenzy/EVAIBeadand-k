#ifndef RENTTABLEMODEL_H
#define RENTTABLEMODEL_H

#include <QSqlRelationalTableModel>

class RentTableModel: public QSqlRelationalTableModel
{
     Q_OBJECT
public:
    RentTableModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; // adatlekérdezés felüldefiniálása
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole); // adatbeállítás

private:
    void setupModel(); // modell beállítása

};

#endif // RENTTABLEMODEL_H
