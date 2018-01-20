#include "esemenytablemodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

EsemenyTableModel::EsemenyTableModel(QObject *parent) : QSqlRelationalTableModel(parent)
{
    setupModel();

}

int EsemenyTableModel::columnCount(const QModelIndex& parent) const
{
    return QSqlRelationalTableModel::columnCount(parent) + 2;
}

QVariant EsemenyTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();


    if  (index.column() == 4 && role == Qt::DisplayRole) // apartmanok száma
    {
        QSqlQuery query;
        QSqlQuery foglalthelyek;
        foglalthelyek.exec("select count(*) from helyek where eloadas_id = "+ this->data(this->index(index.row(), 0)).toString() +" and status = 1");
        query.exec("select sorok_oszlopok from termek where id = " + this->data(this->index(index.row(), 0)).toString());
        if (query.next())
        {
            if(foglalthelyek.next())
              return QVariant(( query.value(0).toInt() * query.value(0).toInt() ) - foglalthelyek.value(0).toInt() );
            else
                 return QVariant( query.value(0).toInt() * query.value(0).toInt() );
         }
         else
              return QVariant(0);
    }
    else if (index.column() == 5 && role == Qt::DisplayRole)
    {
        QSqlQuery query;
        query.exec("select sorok_oszlopok from termek where id = " + this->data(this->index(index.row(), 0)).toString());
        if (query.next())
        {
           return QVariant(( query.value(0).toInt() * query.value(0).toInt() ) );

        }
        else
           return QVariant(0);
    }
    else
    {
        return QSqlRelationalTableModel::data(index, role);
    }
}



void EsemenyTableModel::setupModel()
{
    setTable("eloadasok");
    setSort(3, Qt::AscendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setHeaderData(0, Qt::Horizontal, trUtf8("Azonosító"));
    setHeaderData(1, Qt::Horizontal, trUtf8("Film"));
    setHeaderData(2, Qt::Horizontal, trUtf8("Terem"));
    setHeaderData(3, Qt::Horizontal, trUtf8("Időpont"));
    setHeaderData(4, Qt::Horizontal, trUtf8("Szabad"));
    setHeaderData(5, Qt::Horizontal, trUtf8("Székek száma"));

    setRelation(1, QSqlRelation("filmek", "id", "cim"));
    setRelation(2, QSqlRelation("termek", "id", "nev"));
}



