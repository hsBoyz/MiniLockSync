#include "mainwindow.h"
#include "steerer.h"
#include "watcher.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    Steerer *w = new Steerer();
    w->start();


    //MainWindow w;
    //w.show();

    QFileSystemWatcher watcher;
    Settingsmanager *setman = new Settingsmanager();
    Watcher *watch = new Watcher();

    watcher.addPath(setman->returnSetting("directory", setman->getKeyAtPosition("directory", 0)));

    QObject::connect(&watcher, SIGNAL(directoryChanged(QString)), watch, SLOT(showModified(QString)));




    return a.exec();
}
