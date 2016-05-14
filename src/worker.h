#ifndef WORKER_H
#define WORKER_H


#include <QThread>
#include <QDebug>

class Worker : public QThread
{

public:
    explicit Worker();

    void run();
    bool stop;
signals:

public slots:
    void DoWork();
};

#endif // WORKER_H
