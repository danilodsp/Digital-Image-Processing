#include <QtGui/QApplication>
#include "pdi.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pdi w;
    w.show();
    return a.exec();
}
