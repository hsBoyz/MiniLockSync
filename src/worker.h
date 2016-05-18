#ifndef WORKER_H
#define WORKER_H

#include "queue.h"
#include "login.hpp"
#include "settingsmanager.h"
#include "handlefiles.h"
#include <uCryptLib.h>
#include <QDir>
#include <QThread>
#include <QDebug>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker();
    ~Worker();

private:
    Queue *queue;
    QFileInfo getDir();
    login *log;
    Settingsmanager *settingsmanager;
    Handlefiles *filesHandler;

signals:
    void finished();
    void error(QString err);

public slots:
    void process(int encryptionOn);

    void printDir();
};

#endif // WORKER_H
