#include "QtWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidget w;
    w.show();
    return a.exec();
}
