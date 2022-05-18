#include "shibi.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    shibi w;
    w.show();
    return a.exec();
}
