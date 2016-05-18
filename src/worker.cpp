#include "worker.h"
#include "mainwindow.h"
#include <Qdir>
#include <QThread>

Worker::Worker()
{
    queue = new Queue();
    log = new login();
    settingsmanager = new Settingsmanager();
    filesHandler = new Handlefiles();

    QThread *thread2 = new QThread();
    queue->moveToThread(thread2);
    connect(thread2, SIGNAL(started()), queue, SLOT(fillQueue()));
    connect(queue, SIGNAL(finished()), thread2, SLOT(quit()));
    thread2->start();
}

Worker::~Worker()
{

}

void Worker::process(int encryptionOn)
{
    int testint;
    QFileInfo fromDir;
    QStringList dirsToEncryp = settingsmanager->loadSettings(MainWindow::settingsKeyForPaths);
    QString toWork = settingsmanager->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir");
    QString toCloud = settingsmanager->returnSetting(MainWindow::settingsKeyForCloudDirPath, "clouddir");


    do
    {
        //fromDir = getDir();
        //qDebug() << fromDir.path();

        /*
        foreach (QString nameOfDir, dirsToEncryp) {
            QString from = fromDir.path() + QDir::separator();

            QString toNewWork = filesHandler->createDir(toWork, nameOfDir) + QDir::separator();
            QString toNewCloud = filesHandler->createDir(toCloud, nameOfDir) + QDir::separator();

            qDebug() << "from: " << from;
            qDebug() << "toNewCloud: " << toNewCloud;
            qDebug() << "toNewWork: " << toNewWork;

            if(fromDir.isFile())
            {
                from += fromDir.fileName();
                toNewCloud += fromDir.fileName();
                toNewWork += fromDir.fileName();

                if (QFile::exists(toNewCloud) || QFile::exists(toNewWork))
                {
                    qDebug() << "Worker process: file already exists";
                }
                if (encryptionOn == 1) {
                    uCrypt::uCryptLib mainSession = log->getMainSession();

                    if (QFile::copy(fromDir.absoluteFilePath(), toNewCloud)== false) {
                        qDebug() << "Worker process encryptionOn: file not copied";
                    }
                    if (mainSession.EncryptFile(fromDir.baseName().toStdString(), toNewCloud.toStdString(), nullptr, 0) != 0) {
                        qDebug() << "Worker process encryptionOn: something went wrong with the encryption";
                    }
                    QFile::remove(toNewCloud);

                }
                else if (QFile::copy(from, toNewWork) == false)
                {
                    qDebug() << "from: " << fromDir.absoluteFilePath();
                    qDebug() << "to: " << toNewWork;
                    qDebug() << "Worker process: file not copied";
                }

            }
            else if (fromDir.isDir())
            {
                QDir dir(fromDir.absolutePath());
                if (dir.mkpath(toNewCloud) == false || dir.mkpath(toNewWork) == false)
                {
                    qDebug() << "Worker process: dir not created";
                }
            }
        }
        */
    } while (getDir().path() != ".");



    emit finished();
    }




QFileInfo Worker::getDir()
{
    return queue->getQDir();
}

void Worker::printDir()
{
    qDebug() << queue->getQDir().path();
}

/*

bool Worker::copy_dir(QString fromDir, QString toDir, bool encryptionOn)
{
    //get all directories which user has specified to encrypt
    QStringList dirsToEncryp = settingsmanager->loadSettings(MainWindow::settingsKeyForPaths);
    //Load first, and in this case only, key from specified working direcotries
    QString toWork = settingsmanager->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir");
    QString toCloud = settingsmanager->returnSetting(MainWindow::settingsKeyForCloudDirPath, "clouddir");

    QDir dir;
    dir.setPath(fromDir);

    fromDir += QDir::separator();
    toDir += QDir::separator();

    foreach (QString copyfile, dir.entryList(QDir::Files))
    {
        QString from = fromDir + copyfile;
        QString to = toDir + copyfile;

        if (QFile::exists(to))
        {
            return false;
        }

        if (encryptionOn) {
            uCrypt::uCryptLib mainSession = log->getMainSession();

            if (QFile::copy(from, to)== false) {
                return false;
            }
            //checkForErrors(mainSession.EncryptFile(copyfile.toStdString(), to.toStdString(), nullptr, 0));
            if (mainSession.EncryptFile(copyfile.toStdString(), toDir.toStdString(), nullptr, 0) != 0) {
                return false;
            }
            QFile::remove(to);

        }
        else if (QFile::copy(from, to) == false)
        {
            return false;
        }

    }

    foreach (QString copyDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QString from = fromDir + copyDir;
        QString to = toDir + copyDir;

        if (dir.mkpath(to) == false)
        {
            return false;
        }
        if (copy_dir_recursive(from, to, encryptionOn) == false)
        {
            return false;
        }
    }

    return true;
}



void Worker::copyDirectory(){
    QStringList dirsToEncryp = settingsmanager->loadSettings(MainWindow::settingsKeyForPaths);
    QString toWork = settingsmanager->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir");
    QString toCloud = settingsmanager->returnSetting(MainWindow::settingsKeyForCloudDirPath, "clouddir");

    foreach (QString nameOfDir, dirsToEncryp) {
        QString from = settingsmanager->returnSetting(MainWindow::settingsKeyForPaths, nameOfDir);

        QString toNewWork = filesHandler->createDir(toWork, nameOfDir);
        QString toNewCloud = filesHandler->createDir(toCloud, nameOfDir);
        filesHandler->copy_dir(from, toNewWork, false);
        filesHandler->copy_dir(from, toNewCloud, true);
    }
}



*/
