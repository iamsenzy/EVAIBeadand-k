#ifndef EVENTRENTDIALOG_H
#define EVENTRENTDIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class EventRentDialog;
}

class EventRentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EventRentDialog(QWidget *parent = 0);
    ~EventRentDialog();

    void setEsemeny(int id, int meret, QString esemenyName, QString eventRoom, QString eventDate); // apartman beállítása
    void setModel(QSqlTableModel* rentModel); // modellek beállítása

private slots:
    void rentButton_Clicked(); // foglalás


private:
    void setupGui();

    Ui::EventRentDialog *ui;

    int eventId,m;
    QSqlTableModel* rentTableModel;

};

#endif // EVENTRENTDIALOG_H
