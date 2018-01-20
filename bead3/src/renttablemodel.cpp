#include "renttablemodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

RentTableModel::RentTableModel(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setupModel();
}

QVariant RentTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();

    if (index.column() == 5)
    {
        switch (role)
        {
            case Qt::TextAlignmentRole:
                return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
            case Qt::CheckStateRole:
                if (QSqlRelationalTableModel::data(index, Qt::DisplayRole).toInt() == 1)
                    return QVariant(Qt::Checked);
                else
                    return QVariant(Qt::Unchecked);
            default:
                return QVariant();
        }
    }
    else
        return QSqlRelationalTableModel::data(this->index(index.row(), index.column()), role);
}

bool RentTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.column() == 5 && role == Qt::CheckStateRole) // a foglalható oszlop
    {
        if (value.toInt() == Qt::Checked) // ha be lett jelölve
            return QSqlRelationalTableModel::setData(index, 1);
        else
            return QSqlRelationalTableModel::setData(index, 0);
    }
    else
        return QSqlRelationalTableModel::setData(index, value);

}

void RentTableModel::setupModel()
{
    setTable("helyek");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setHeaderData(1, Qt::Horizontal, trUtf8("Esemeny"));
    setHeaderData(2, Qt::Horizontal, trUtf8("Terem"));
    setHeaderData(3, Qt::Horizontal, trUtf8("Sor"));
    setHeaderData(4, Qt::Horizontal, trUtf8("Oszlop"));
    setHeaderData(5, Qt::Horizontal, trUtf8("Statusz"));
    setRelation(2, QSqlRelation("termek", "id", "nev"));
}
