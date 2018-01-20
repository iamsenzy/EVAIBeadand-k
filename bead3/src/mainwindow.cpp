#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include "teremtablemodel.h"
#include "esemenytablemodel.h"
#include "renttablemodel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    mdiArea = new QMdiArea; // mdi ablakterület létrehozása
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    esemenyTableModel = 0;
    teremTableModel = 0;
    rentTableModel = 0;

    setupMenu();
    setupModels();

    setWindowTitle(trUtf8("Mozi alkalmazás"));
}

MainWindow::~MainWindow()
{
    delete teremTableModel;
    delete esemenyTableModel;
    delete esemenyTableDelegate;
    delete rentTableModel;
    if (rentTableModel !=0) delete rentTableModel;
    if (esemenyTableModel != 0) delete esemenyTableModel;
    if (teremTableModel != 0) delete teremTableModel;

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows(); // minden ablak bezárása
}


void MainWindow::rentMakeAction_Triggered()
{
    eventListWidget = new EventListWidget(this);
    eventListWidget->setModel(esemenyTableModel,teremTableModel,rentTableModel);
    mdiArea->addSubWindow(eventListWidget);
    eventListWidget->show();
}

void MainWindow::filmAction_Triggered()
{
    filmEditorWidget = new TableEditorWidget(trUtf8("Filmek szerkesztése"), this);
    QVector<int> columnsHidden = QVector<int>(1); // rejtett oszlop beállítása
    columnsHidden[0] = 0;
    filmEditorWidget->setModel(filmTableModel, columnsHidden);

    mdiArea->addSubWindow(filmEditorWidget); // betöltjük beágyazott ablakként
    filmEditorWidget->show();
}

void MainWindow::esemenyAction_Triggered()
{
    esemenyEditorWidget = new TableEditorWidget(trUtf8("Esemenyek szerkesztése"), this);
    QVector<int> columnsHidden = QVector<int>(2); // rejtett oszlop beállítása
    columnsHidden[0] = 0;
    esemenyEditorWidget->setModel(esemenyTableModel, esemenyTableDelegate, columnsHidden);

    mdiArea->addSubWindow(esemenyEditorWidget); // betöltjük beágyazott ablakként
    esemenyEditorWidget->show();
}

void MainWindow::teremAction_Triggered()
{
    teremEditorWidget = new TableEditorWidget(trUtf8("Termek szerkesztése"), this);
    QVector<int> columnsHidden = QVector<int>(1); // rejtett oszlop beállítása
    columnsHidden[0] = 0;
    teremEditorWidget->setModel(teremTableModel, columnsHidden);

    mdiArea->addSubWindow(teremEditorWidget); // betöltjük beágyazott ablakként
    teremEditorWidget->show();
}

void MainWindow::rentAction_Triggered()
{
    rentEditorWidget = new TableEditorWidget(trUtf8("Helyek szerkesztése"), this);
    QVector<int> columnsHidden = QVector<int>(1); // rejtett oszlop beállítása
    columnsHidden[0] = 0;
    rentEditorWidget->setModel(rentTableModel, columnsHidden);

    mdiArea->addSubWindow(rentEditorWidget); // betöltjük beágyazott ablakként
    rentEditorWidget->show();
}




void MainWindow::setupMenu()
{
    rentMenu = menuBar()->addMenu(trUtf8("&Foglalások")); // menü létrehozása

    rentMakeAction = new QAction(trUtf8("Új foglalás"), this);
    rentMakeAction->setStatusTip(trUtf8("Új foglalás létrehozása."));
    connect(rentMakeAction, SIGNAL(triggered()), this, SLOT(rentMakeAction_Triggered()));
    rentMenu->addAction(rentMakeAction);

    administerMenu = menuBar()->addMenu(trUtf8("&Adminisztráció"));

    filmAction = new QAction(trUtf8("Filmek szerkesztése"), this);
    connect(filmAction, SIGNAL(triggered()), this, SLOT(filmAction_Triggered()));
    administerMenu->addAction(filmAction);

    esemenyAction = new QAction(trUtf8("Esemenyek szerkesztése"), this);
    connect(esemenyAction, SIGNAL(triggered()), this, SLOT(esemenyAction_Triggered()));
    administerMenu->addAction(esemenyAction);

    teremAction = new QAction(trUtf8("Termek szerkesztése"), this);
    connect(teremAction, SIGNAL(triggered()), this, SLOT(teremAction_Triggered()));
    administerMenu->addAction(teremAction);

    rentAction = new QAction(trUtf8("Helyek szerkesztése"), this);
    connect(rentAction, SIGNAL(triggered()), this, SLOT(rentAction_Triggered()));
    administerMenu->addAction(rentAction);

}

void MainWindow::setupModels()
{
    // inicializáljuk a modelleket
    teremTableModel = new TeremTableModel();
    teremTableModel->select();

    esemenyTableModel = new EsemenyTableModel();
    esemenyTableModel->select();

    rentTableModel = new RentTableModel();
    rentTableModel->select();

    esemenyTableDelegate = new EsemenyTableDelegate();

    filmTableModel = new QSqlTableModel();
    filmTableModel->setTable("filmek");
    filmTableModel->setHeaderData(1, Qt::Horizontal, trUtf8("Cím"));
    filmTableModel->setHeaderData(2, Qt::Horizontal, trUtf8("Származás"));
    filmTableModel->setHeaderData(3, Qt::Horizontal, trUtf8("Szinkronizált"));
    filmTableModel->setHeaderData(4, Qt::Horizontal, trUtf8("Rendező"));
    filmTableModel->setHeaderData(5, Qt::Horizontal, trUtf8("Szinopszis"));
    filmTableModel->setHeaderData(6, Qt::Horizontal, trUtf8("Hossz"));
    filmTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);


}
