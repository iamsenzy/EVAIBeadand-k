#include "eventrentdialog.h"
#include "ui_eventrentdialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>

EventRentDialog::EventRentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventRentDialog)
{
    ui->setupUi(this);

    setWindowTitle(trUtf8("Hely foglalása"));

    rentTableModel = 0;

}

EventRentDialog::~EventRentDialog()
{
    delete ui;
}

void EventRentDialog::rentButton_Clicked()
{
    if (eventId == 0 || rentTableModel == 0)
    // ha valami nincs beállítva, kilépünk
        return;


    QSqlQueryModel foglalthely;
    foglalthely.setQuery("select count(*) from helyek where esemeny_id = "+ QString::number(eventId) +
                         " and sor = "+ ui->sorComboBox->currentText() + " and oszlop = "+ ui->sorComboBox->currentText() +
                         " and status = 0" );

    if (foglalthely.rowCount() > 0)
    {
        QMessageBox::warning(this, trUtf8("Hiba!"), trUtf8("A megadott időpontban már van foglalás az apartmanra!"));
        return;
    }

    QSqlQuery a;
    a.exec("select terem_id from eloadasok where id = "+ QString::number(eventId) );
    QVariant eventRoom;
    if(a.next())
    eventRoom =QVariant(( a.value(0).toInt()));

    if (QMessageBox::question(this, trUtf8("Foglalás rögzítése"), trUtf8("Biztos rögzíti a foglalást?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
        rentTableModel->insertRow(0); // sor beszúrása
        rentTableModel->setData(rentTableModel->index(0,1), eventId);
        rentTableModel->setData(rentTableModel->index(0,2), eventRoom);
        rentTableModel->setData(rentTableModel->index(0,3), ui->sorComboBox->currentText().toInt());
        rentTableModel->setData(rentTableModel->index(0,4), ui->oszlopComboBox->currentText().toInt());
        rentTableModel->setData(rentTableModel->index(0,5), 1);

        rentTableModel->submitAll(); // változtatás mentése
        close(); // ablak bezárása
    }
}


void EventRentDialog::setEsemeny(int id, int meret, QString esemenyName, QString eventRoom, QString eventDate)
{
    eventId=id;
    m=meret;
    ui->eventLabel->setText(esemenyName);
    ui->datumLabel->setText(eventDate);
    ui->teremLabel->setText(eventRoom);

}

void EventRentDialog::setModel(QSqlTableModel* rentModel)
{

    rentTableModel = rentModel;
    rentTableModel->select();
    ui->sorComboBox->clear();
    ui->oszlopComboBox->clear();

    for(int i=1; i <= m; i++)
    {
         ui->sorComboBox->addItem(QString::number(i));
         ui->oszlopComboBox->addItem(QString::number(i));
    }

    setupGui();
}

void EventRentDialog::setupGui()
{
    connect(ui->rentButton, SIGNAL(clicked()), this, SLOT(rentButton_Clicked()));
}
