#include "worker.h"
#include "mainwindow.h"
#include "window.h"
#include <Qdir>
#include <QThread>

Worker::Worker()
{
    filesHandler = new Handlefiles();

}

Worker::~Worker()
{

}

void Worker::processCopyAddedFolders() {
    filesHandler->copyDirectory();
    emit finished();
}


void Worker::process()
{
    filesHandler->checkAndCopyWorkDir();
    filesHandler->copyEncryptedFromCloud();
    emit finished();
}

void Worker::processSyncWork() {
    filesHandler->checkAndCopyWorkDir();
    emit finished();
}

void Worker::processSyncCloud()
{
    filesHandler->copyEncryptedFromCloud();
    emit finished();
}





