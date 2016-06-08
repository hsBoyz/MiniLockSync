#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>

#include "mainwindow.h"
#include "window.h"
#include "steerer.h"

#include "login.hpp"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Translation
    QTranslator editTranslator;
    QString filename;
    filename = QString("MiniLockSync_%1").arg(QLocale::system().name());
    editTranslator.load(":/Languages/MiniLockSync_de.qm");
    a.installTranslator(&editTranslator);


    a.setQuitOnLastWindowClosed(false);
    MainWindow w;
    //login l;
    login::GetInstance().show();



    //w.show();

    return a.exec();
}
