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
<<<<<<< HEAD
    QDir dir(QDir::currentPath() + "/../../src/");
    //qDebug() << dir.absolutePath();

    /* /build/build-MiniLockSync-Desktop_Qt_5_6_0_MSVC2015-Release/release/MiniLockSync_de.qm    and      /MiniLockSync_de.ts ! */
    editTranslator.load(filename, dir.currentPath());                      //qApp->applicationDirPath()); ///!!!!!!!!!!!!!!!!!! ToDo


=======
    //qDebug() << filename;
    if (filename == "MiniLockSync_de_DE"){
    editTranslator.load(":/Languages/MiniLockSync_de.qm");
    }
>>>>>>> GUI_Luca
    a.installTranslator(&editTranslator);


    a.setQuitOnLastWindowClosed(false);
    MainWindow w;
    //login l;
    login::GetInstance().show();



    //w.show();

    return a.exec();
}
