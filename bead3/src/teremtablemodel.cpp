#include "teremtablemodel.h"

TeremTableModel::TeremTableModel(QObject *parent) : QSqlRelationalTableModel(parent)
{
    setupModel();
}



void TeremTableModel::setupModel()
{
    setTable("termek");
    setSort(1, Qt::AscendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setHeaderData(0, Qt::Horizontal, trUtf8("Azonosító"));
    setHeaderData(1, Qt::Horizontal, trUtf8("Név"));
    setHeaderData(2, Qt::Horizontal, trUtf8("Sorok és oszlopok száma"));

}

