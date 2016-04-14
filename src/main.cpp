#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QDir mDir("E:/Benutzer/Manuel/Desktop");


    /*
    foreach (QFileInfo mItm, mDir.drives())
    {
        qDebug() << mItm.absoluteFilePath();
    }
    */


    /*

    QString mPath = "E:/Benutzer/Manuel/Desktop/Test";

    if (!mDir.exists(mPath))
    {
        mDir.mkpath(mPath);
        qDebug() << "Created";
    }
    else {
        qDebug() << "Already exists";
    }
    */
    /*
    foreach (QFileInfo mItm, mDir.entryInfoList())
    {
        //qDebug() << mItm.absoluteFilePath();
        if (mItm.isDir())   qDebug() << "Dir: " << mItm.absoluteFilePath();
        if (mItm.isFile())  qDebug() << "File: " << mItm.absoluteFilePath();

    }
    */

    return a.exec();
}
