#include "labirinth_look.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Labirinth_Look w;
    w.show();

    return a.exec();
}
