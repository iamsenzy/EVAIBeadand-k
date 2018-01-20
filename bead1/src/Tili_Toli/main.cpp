#include "tili_toli.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tili_Toli w;
    w.show();

    return a.exec();
}
