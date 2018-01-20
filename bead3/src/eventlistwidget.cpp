#include "eventlistwidget.h"
#include "ui_eventlistwidget.h"
#include "esemenytabledelegate.h"
#include "esemenytablemodel.h"
#include "teremtablemodel.h"
#include <QSqlQuery>
#include <QMessageBox>

EventListWidget::EventListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventListWidget)
{
    ui->setupUi(this);

    esemenyTableModel = 0;
    teremTableModel = 0;
    rentTableModel = 0;

    setWindowTitle(trUtf8("Események listázása"));


}

EventListWidget::~EventListWidget()
{
    delete ui;

    delete teremSortFilterModel;
    delete nameSortFilterModel;
    delete esemenySelectionModel;
}

void EventListWidget::setModel(QSqlTableModel* esemenyModel, QSqlTableModel* teremModel, QSqlTableModel* rentModel)
{

    esemenyTableModel = esemenyModel;
    teremTableModel = teremModel;

    esemenyTableModel->select();
    teremTableModel->select();

    rentTableModel = rentModel;
    rentTableModel->select();

    setupModel();
    setupFilter();
    setupGui();
}



void EventListWidget::esemenyTableView_DoubleClicked(const QModelIndex& index)
{
    QAbstractItemModel* model = ui->esemenyTableView->model();

    int meret=model->index(index.row(), 5).data().toInt();
    int eventId = model->index(index.row(), 0).data().toInt();

    QString eventName = model->index(index.row(), 1).data().toString();
    QString eventRoom = model->index(index.row(), 2).data().toString();
    QString eventDate = model->index(index.row(), 3).data().toString();

    // a foglalhatóság lekérése
    if ( model->data(model->index(index.row(), 4)).toInt() != 0) // ha foglalható
    {
        rentWidget->setEsemeny(eventId,meret, eventName, eventRoom, eventDate);
        rentWidget->setModel(rentTableModel);
        rentWidget->show();
    }
    else
    {
        QMessageBox::information(this, trUtf8("Hiba!"), trUtf8("Az esemény nem foglalható!"));
    }
}


void EventListWidget::filterButton_Clicked()
{
    if (teremTableModel == 0 || esemenyTableModel == 0)
        return;

    if (ui->filterButton->text() == trUtf8("Szűrés"))
    {
        ui->nameLineEdit->setEnabled(false);
        ui->teremComboBox->setEnabled(false);
        ui->filterButton->setText(trUtf8("Szűrő törlése"));

        QAbstractItemModel *currentModel = esemenyTableModel;

        if (ui->nameLineEdit->text() != "")
        {
            nameSortFilterModel->setSourceModel(currentModel);
            nameSortFilterModel->setFilterKeyColumn(1);
            nameSortFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
            nameSortFilterModel->setFilterRegExp(ui->nameLineEdit->text());
            currentModel = nameSortFilterModel;
        }
        if (ui->teremComboBox->currentText() != trUtf8("mind"))
        {
            teremSortFilterModel->setSourceModel(currentModel);
            teremSortFilterModel->setFilterKeyColumn(2);
            teremSortFilterModel->setFilterFixedString(ui->teremComboBox->currentText());
            currentModel = teremSortFilterModel;
        }

        ui->esemenyTableView->setModel(currentModel);
    }
    else
    {
        ui->nameLineEdit->setEnabled(true);
        ui->teremComboBox->setEnabled(true);
        ui->filterButton->setText(trUtf8("Szűrés"));
        ui->esemenyTableView->setModel(esemenyTableModel);
    }


    disconnect(esemenySelectionModel, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(esemenyTableView_SelectionChanged(QModelIndex)));
    delete esemenySelectionModel;

    esemenySelectionModel = new QItemSelectionModel(ui->esemenyTableView->model());
    ui->esemenyTableView->setSelectionModel(esemenySelectionModel);
    connect(esemenySelectionModel, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(esemenyTableView_SelectionChanged(QModelIndex)));
}

void EventListWidget::esemenyTableView_SelectionChanged(const QModelIndex& index)
{
    if (index.isValid())
    {
        esemenySortFilterModel->setSourceModel(teremTableModel);
        esemenySortFilterModel->setFilterKeyColumn(1);
        esemenySortFilterModel->setFilterFixedString(ui->esemenyTableView->model()->data(ui->esemenyTableView->model()->index(index.row(), 2), Qt::EditRole).toString());
    }

}


void EventListWidget::setupFilter()
{
    ui->teremComboBox->addItem(trUtf8("mind"));
    for (int i = 0; i < teremTableModel->rowCount(); i++)
    {
        ui->teremComboBox->addItem(teremTableModel->index(i, 1).data().toString());
    }
}

void EventListWidget::setupGui()
{
    ui->esemenyTableView->setModel(esemenyTableModel);
    ui->esemenyTableView->resizeColumnsToContents();
    ui->esemenyTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->esemenyTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->esemenyTableView->setItemDelegate(new EsemenyTableDelegate());
    ui->esemenyTableView->setSelectionModel(esemenySelectionModel);
    ui->esemenyTableView->setColumnHidden(0, true);


    connect(ui->filterButton, SIGNAL(clicked()), this, SLOT(filterButton_Clicked()));
    connect(ui->esemenyTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(esemenyTableView_DoubleClicked(QModelIndex)));
    // dupla kattintás kezelése
    connect(esemenySelectionModel, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(esemenyTableView_SelectionChanged(QModelIndex)));

    rentWidget = new EventRentDialog(this);
    rentWidget->setModal(true);

}

void EventListWidget::setupModel()
{
    esemenySelectionModel = new QItemSelectionModel(esemenyTableModel);
    nameSortFilterModel = new QSortFilterProxyModel();
    teremSortFilterModel = new QSortFilterProxyModel();
    esemenySortFilterModel = new QSortFilterProxyModel();
}
