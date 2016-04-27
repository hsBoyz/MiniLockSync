#include "mainwindow.h"
#include "stackedwindow.h"
#include "steerer.h"
#include "login.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

	login l;
	l.show();

    //MainWindow w;

   // Steerer *s = new Steerer();
  //  s->start();

   // w.show();

    return a.exec();
}
