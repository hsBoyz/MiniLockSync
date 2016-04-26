#include "mainwindow.h"
#include "stackedwindow.h"
#include "steerer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Steerer *s = new Steerer();
    s->start();

    w.show();

    return a.exec();
}
