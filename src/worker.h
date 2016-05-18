#ifndef WORKER_H
#define WORKER_H

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
    login *log;
    Settingsmanager *settingsmanager;
    Handlefiles *filesHandler;

    void copyDirectory();
signals:
    void finished();
    void error(QString err);

public slots:
    void process(int encryptionOn);

};

#endif // WORKER_H
