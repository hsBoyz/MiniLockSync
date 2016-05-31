#ifndef WORKER_H
#define WORKER_H

#include "handlefiles.h"
#include "window.h"
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
    Window *window;

signals:
    void finished();
    void error(QString err);

public slots:
    void set_StatusBar_Started();
    void process();
    void processSyncCloud();

};

#endif // WORKER_H
