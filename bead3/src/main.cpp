#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("cinemadb");
    db.setUserName("root");
    db.setPassword("bertalan");

    if (db.open()) // kapcsolat megnyitása
    {
        db.close(); // rögtön be is zárhatjuk, a későbbi műveletekhez nem kell


        MainWindow *m = new MainWindow();
        m->show();

    }
    else
    {
        QMessageBox::critical(0, QObject::trUtf8("Hiba!"), QObject::trUtf8("Nem sikerült kapcsolódni az adatbázis-szerverhez."));
    }



    return a.exec();

}
