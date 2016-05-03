#include "mainwindow.h"
#include "steerer.h"
#include "login.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
   // MainWindow w;
	login l;
	l.show();
	
    Steerer *s = new Steerer();
    s->start();

    //w.show();

    return a.exec();
}
