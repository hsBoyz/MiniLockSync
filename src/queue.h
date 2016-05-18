#ifndef QUEUE_H
#define QUEUE_H

#include "settingsmanager.h"
#include <QObject>
#include <QQueue>
#include <QThread>
#include <QFileInfo>

class Queue : public QObject
{
    Q_OBJECT
public:
    explicit Queue(QObject *parent = 0);

private:
    QQueue<QFileInfo> queue;
    bool dir_rec(QString fromDir);

    Settingsmanager *settingsmanager;

signals:
    void finished();
public slots:
    void fillQueue();
    QFileInfo getQDir();

};

#endif // QUEUE_H
