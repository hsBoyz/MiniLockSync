#include "mainwindow.h"
#include "steerer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    MainWindow w;

    Steerer *s = new Steerer();
    s->start();

    w.show();

    return a.exec();
}
