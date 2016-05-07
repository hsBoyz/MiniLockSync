#include <QApplication>
#include <QTranslator>
#include <QLocale>

#include "mainwindow.h"
#include "window.h"
#include "steerer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Translation
    QTranslator editTranslator;
    QString filename;
    filename = QString("MiniLockSync_%1").arg(QLocale::system().name());
    editTranslator.load(filename, qApp->applicationDirPath()); ///!!!!!!!!!!!!!!!!!! ToDo
    a.installTranslator(&editTranslator);


    a.setQuitOnLastWindowClosed(false);
    MainWindow w;

    Steerer *s = new Steerer();
    s->start();

    w.show();

    return a.exec();
}
