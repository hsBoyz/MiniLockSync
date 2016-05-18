#include "queue.h"
#include "mainwindow.h"
#include <QRunnable>
#include <QDir>
#include <QDebug>

Queue::Queue(QObject *parent) : QObject(parent)
{
    settingsmanager = new Settingsmanager();
}


void Queue::fillQueue()
{
    QStringList dirsToEncryp = settingsmanager->loadSettings(MainWindow::settingsKeyForPaths);
    foreach(QString nameOfDir, dirsToEncryp) {
        QString from = settingsmanager->returnSetting(MainWindow::settingsKeyForPaths, nameOfDir);
        qDebug() << "from: " << from;
        dir_rec(from);
    }
    emit finished();
}

bool Queue::dir_rec(QString fromDir)
{
    QDir dir;
    dir.setPath(fromDir);
    int i = 0;

    fromDir += QDir::separator();

    foreach (QString copyfile, dir.entryList(QDir::Files))
    {
        QString from = fromDir + copyfile;
        //qDebug() << "file: " << from;
        queue.enqueue(QFileInfo(from));

        qDebug() << "int: " << i;
        intQueue.enqueue(i);
        i++;

    }

    foreach (QString copyDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QString from = fromDir + copyDir;
        //qDebug() << "dir: " << from;
        queue.enqueue(QFileInfo(from));

        qDebug() << "int: " << i;
        intQueue.enqueue(i);
        i++;

        if (dir_rec(from) == false)
        {
            return false;
        }
    }

    return true;
}

QFileInfo Queue::getQDir()
{

    if (queue.isEmpty()) {
        qDebug() << "Queue getQDir: Queue is empty";
        return QFileInfo("");
    }
    else {
        //qDebug() << "getQDir: " << queue.dequeue().path();
        return queue.dequeue();
    }
}
