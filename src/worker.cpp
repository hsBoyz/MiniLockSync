#include "worker.h"
#include "mainwindow.h"
#include <Qdir>
#include <QThread>

Worker::Worker()
{
    filesHandler = new Handlefiles();
    window = new Window();
}

Worker::~Worker()
{

}

void Worker::set_StatusBar_Started(){


        QLabel *test = new QLabel;
        test->setPixmap(QPixmap(":/icons/images/sync_icon.png"));
        Window.ui->statusBar->insertPermanentWidget(0, test, 0);

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





