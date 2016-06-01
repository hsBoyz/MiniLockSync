#ifndef WORKER_H
#define WORKER_H

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
    Handlefiles *filesHandler;


signals:
    void finished();
    void error(QString err);

public slots:

    void process();
    void processSyncCloud();

};

#endif // WORKER_H
