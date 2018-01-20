#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class endDialog: public QDialog
{
public:
    explicit endDialog(int lepesek,QWidget *parent = 0);
private:
    int _lepesek;
    QLabel *_label;
    QLabel *_label2;
    QPushButton *_ujButton;
    QPushButton *_exButton;
};

#endif // ENDDIALOG_H
