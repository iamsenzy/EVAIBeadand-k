#ifndef EVENTLISTWIDGET_H
#define EVENTLISTWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>
#include <QItemDelegate>
#include <eventrentdialog.h>
#include "esemenytabledelegate.h"

namespace Ui {
class EventListWidget;
}

class EventListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EventListWidget(QWidget *parent = 0);
    ~EventListWidget();

    void setModel(QSqlTableModel* esemenyModel, QSqlTableModel* teremModel, QSqlTableModel* rentModel);
        // modellek beállítása
private slots:
    void filterButton_Clicked(); // szűrés a felső táblára
    void esemenyTableView_SelectionChanged(const QModelIndex& index); // szűrés az alsó táblára
    void esemenyTableView_DoubleClicked(const QModelIndex& index); // duplakattintás a táblán

private:
    void setupFilter(); // beállító műveletek
    void setupGui();
    void setupModel();

    Ui::EventListWidget *ui;
    EventRentDialog* rentWidget;

    //QSqlTableModel* cityTableModel; // táblamodellek
    QSqlTableModel* esemenyTableModel;
    QSqlTableModel* teremTableModel;
    QSqlTableModel* rentTableModel;
   // QSqlTableModel* customerTableModel;
    QItemSelectionModel* esemenySelectionModel; // kiválasztás kezelése az épületek táblára
    QItemDelegate* delegate; // delegált

    QSortFilterProxyModel *nameSortFilterModel; // szűrő és rendező modellek
    QSortFilterProxyModel *teremSortFilterModel;
    QSortFilterProxyModel *esemenySortFilterModel;

    EsemenyTableDelegate* esemenyTableDelegate;

};

#endif // EVENTLISTWIDGET_H
