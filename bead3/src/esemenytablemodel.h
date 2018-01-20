#ifndef ESEMENYTABLEMODEL_H
#define ESEMENYTABLEMODEL_H

#include <QSqlRelationalTableModel>

class EsemenyTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    EsemenyTableModel(QObject *parent = 0);
    int columnCount(const QModelIndex & parent = QModelIndex()) const; // oszlopszám felüldefiniálása
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; // adatlekérdezés felüldefiniálása

private:
    void setupModel(); // modell beállítása


};

#endif // ESEMENYTABLEMODEL_H
