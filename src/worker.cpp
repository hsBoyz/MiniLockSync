#include "worker.h"
#include "mainwindow.h"
#include <Qdir>
#include <QThread>

Worker::Worker()
{
    filesHandler = new Handlefiles();
}

Worker::~Worker()
{

}

void Worker::process()
{
    filesHandler->copyDirectory();
    emit finished();
}

void Worker::processSyncCloud()
{
    filesHandler->copyEncryptedFromCloud();
    emit finished();
}





