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

    static int errorCounter;
    static QStringList errorFilesList;

private:
    Handlefiles *filesHandler;
    QString returnDirectoryCleanedPath(QString path);

signals:
    void finished();
    void error(QString err);

public slots:

    void processCopyAddedFolders();
    void process();
    void processSyncWork();
    void processSyncCloud();
    void processAddFolder(QString path);

};

#endif // WORKER_H
