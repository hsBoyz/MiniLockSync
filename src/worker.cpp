#include "worker.h"
#include "mainwindow.h"
#include "window.h"
#include <Qdir>
#include <QThread>
#include <QMessageBox>

int Worker::errorCounter = 0;
QStringList Worker::errorFilesList;

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

void Worker::processAddFolder(QString path) {
    Settingsmanager *setman = new Settingsmanager();

    QFileInfo fPath(path);
    QString dirCleanedPath = returnDirectoryCleanedPath(QString(FileWindow::currentDirPath));
    QString workDir = setman->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir") + QDir::separator() + dirCleanedPath;

    QDir dir(workDir + QDir::separator() + fPath.baseName());

    if (path == "") {
        //Do nothing when user cancel dialog
    }
    else if (dir.exists()) {
        QMessageBox msgBox;
        msgBox.setInformativeText(tr("Folder already exists. Please remove or rename."));
        msgBox.exec();
    }
    else
    {

        QString cloudDir = setman->returnSetting(MainWindow::settingsKeyForCloudDirPath, "clouddir") + QDir::separator() + dirCleanedPath;
        QString toWorkDir = filesHandler->createDir(workDir, fPath.baseName());
        QString toCloudDir = filesHandler->createDir(cloudDir, fPath.baseName());
        bool cloudBool = filesHandler->copy_dir_recursive(path, toCloudDir, true);
        bool workBool = filesHandler->copy_dir_recursive(path, toWorkDir, false);

        if (cloudBool == true && workBool == true) {
            filesHandler->delete_dir_recursive(path);
        }
    }
    emit finished();
}


QString Worker::returnDirectoryCleanedPath(QString path) {
        Settingsmanager *setman = new Settingsmanager();
        QString defaultPath = setman->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir");
        int removeTo = defaultPath.length() + 1;    //+1 to also eliminate the last seperator

        return path.remove(0,removeTo);
    }


