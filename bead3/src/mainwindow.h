#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "tableeditorwidget.h"
#include "eventlistwidget.h"
#include "esemenytabledelegate.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event); // ablak bezárása

private slots:
    void rentMakeAction_Triggered(); // menüpontok eseménykezelői
    void filmAction_Triggered();
    void esemenyAction_Triggered();
    void teremAction_Triggered();
    void rentAction_Triggered();


private:
    void setupMenu(); // menü létrehozása
    void setupModels(); // modellek létrehozása

    QMdiArea* mdiArea;
    QMenu* rentMenu;
    QMenu* administerMenu;// menü

    QAction* rentMakeAction;// menüpontok
    QAction* filmAction;
    QAction* esemenyAction;
    QAction* teremAction;
    QAction* rentAction;


    EventListWidget* eventListWidget;

    TableEditorWidget* filmEditorWidget;
    TableEditorWidget* esemenyEditorWidget;
    TableEditorWidget* teremEditorWidget;
    TableEditorWidget* rentEditorWidget;


    QSqlTableModel* esemenyTableModel; // táblamodellek
    QSqlTableModel* teremTableModel;
    QSqlTableModel* rentTableModel;
    QSqlTableModel* filmTableModel;


    EsemenyTableDelegate* esemenyTableDelegate;

};

#endif // MAINWINDOW_H
