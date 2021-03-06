#include "handlefiles.h"
#include "settingsmanager.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QObject>

Handlefiles::Handlefiles()
{
    settingsmanager = new Settingsmanager();
}

bool Handlefiles::copy_dir_recursive(QString fromDir, QString toDir, bool encryptionOn)
{
    qDebug() << encryptionOn;
    qDebug() << fromDir;
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

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
            QFileInfo fromInfo(from);
            QFileInfo toInfo(to);
            if (fromInfo.lastModified().toMSecsSinceEpoch() > toInfo.lastModified().toMSecsSinceEpoch()) {
                if (encryptionOn) {
                    QFile::remove(to);
                    encryptAndCopy(from, to, copyfile, toDir);
                }
                else {
                QFile::remove(to);
                QFile::copy(from, to);
                }
            }
        }
        else if (encryptionOn) {
            encryptAndCopy(from, to, copyfile, toDir);
        }
        else if (QFile::copy(from, to) == false)
        {
            //return false;
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

bool Handlefiles::copy_dir_recursive_cloud(QString fromDir, QString toDir) {
    QDir dir;
    dir.setPath(fromDir);

    fromDir += QDir::separator();
    toDir += QDir::separator();

    foreach (QString copyfile, dir.entryList(QDir::Files))
    {
        QString from = fromDir + copyfile;
        QString to = toDir + copyfile;
        QFileInfo fromInfo(from);
        QFileInfo toInfo(to);

        QFileInfo toInfoBase(toInfo.completeBaseName());    //includes path of file in to-dir without .encrypted suffix

        if (fromInfo.suffix() == "encrypted") {
            if (QFile::exists(toInfoBase.absoluteFilePath()))
            {
                qDebug() << toInfoBase.absoluteFilePath();
                qDebug() <<  toInfoBase.lastModified().toMSecsSinceEpoch();

                if (fromInfo.lastModified().toMSecsSinceEpoch() <  toInfoBase.lastModified().toMSecsSinceEpoch()) {
                    qDebug() << TAG << "copy_dir_recursive, fromInfo: " << fromInfo.lastModified();
                    qDebug() << TAG << "copy_dir_recursive, toInfo: " << toInfo.lastModified();

                    QFile::remove(toInfo.completeBaseName());
                    decryptAndCopy(from, to, copyfile, toDir);

                }
            }

            else if (decryptAndCopy(from, to, copyfile, toDir) == false)
            {
                return false;
            }
       }
    }

    foreach (QString copyDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QString from = fromDir + copyDir;
        QString to = toDir + copyDir;

        QFileInfoList list = QDir(from).entryInfoList(QDir::Files);

        if (checkListForEncryptedFiles(list)) {
            if (dir.mkpath(to) == false)
            {
                return false;
            }
            if (copy_dir_recursive_cloud(from, to) == false)
            {
                return false;
            }
        }
        else {
            if (copy_dir_recursive_cloud(from, to) == false)
            {
                return false;
            }
        }
    }

    return true;
}

bool Handlefiles::delete_dir_recursive(QString dirDelete)
{
    QDir dir;
    dir.setPath(dirDelete);

    return dir.removeRecursively();
}

QString Handlefiles::createDir(QString path, QString folderName) {

    QDir dir = QDir::root();

    if (!QDir(path + QDir::separator() + folderName).exists()) {
        dir.mkpath(path + QDir::separator() + folderName);
    }
    else {
        //qDebug() << "handlefiles createdir folder already exists";
    }
    return path + QDir::separator() + folderName;


}

void Handlefiles::copyDirectory(){
    QStringList dirsToEncryp = settingsmanager->loadSettings(MainWindow::settingsKeyForPaths);
    QString toWork = settingsmanager->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir");
    QString toCloud = settingsmanager->returnSetting(MainWindow::settingsKeyForCloudDirPath, "clouddir");
    foreach (QString nameOfDir, dirsToEncryp) {
        QString from = settingsmanager->returnSetting(MainWindow::settingsKeyForPaths, nameOfDir);

        QString toNewWork = createDir(toWork, nameOfDir);
        QString toNewCloud = createDir(toCloud, nameOfDir);
        copy_dir_recursive(from, toNewWork, false);
        copy_dir_recursive(from, toNewCloud, true);

        //delete originals after copying into working directory
        delete_dir_recursive(from);
    }


}

void Handlefiles::checkAndCopyWorkDir() {
    QString fromWork = settingsmanager->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir");
    QString toCloud = settingsmanager->returnSetting(MainWindow::settingsKeyForCloudDirPath, "clouddir");

    copy_dir_recursive(fromWork, toCloud, true);

}


void Handlefiles::copyEncryptedFromCloud() {
    QString toWork = settingsmanager->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir");
    QString fromCloud = settingsmanager->returnSetting(MainWindow::settingsKeyForCloudDirPath, "clouddir");

    copy_dir_recursive_cloud(fromCloud, toWork);
}

bool Handlefiles::encryptAndCopy(QString from, QString to, QString copyfile, QString toDir) {
    uCrypt::uCryptLib mainSession = login::GetInstance().getMainSession();


    if (QFile::copy(from, to)== false) {
        return false;
    }

    int numberOfRecipients = login::GetInstance().ui.comboBox->count();
    std::string *recipients = new std::string[numberOfRecipients];
    recipients[0] = login::GetInstance().ui.comboBox->itemText(0).toStdString();

    int returnCode = mainSession.EncryptFile(copyfile.toStdString(), toDir.toStdString(), recipients, numberOfRecipients);
    if (returnCode != 0) {
        qDebug() << returnCode << ": " << copyfile;
        Worker::errorCounter ++;
        Worker::errorFilesList.append(copyfile);
        return false;
    }

    QFile::remove(to);
}

bool Handlefiles::decryptAndCopy(QString from, QString to, QString copyfile, QString toDir) {
   uCrypt::uCryptLib mainSession = login::GetInstance().getMainSession();

    if (QFile::copy(from, to)== false) {
        return false;
    }

    if (mainSession.DecryptFile(copyfile.toStdString(), toDir.toStdString()) != 0) {
        return false;
    }

    QFile::remove(to);
}

bool Handlefiles::checkListForEncryptedFiles(QFileInfoList list) {
    foreach (QFileInfo fileInfo, list) {
        if (fileInfo.suffix() == "encrypted") {
            qDebug() << "returning true";
            return true;
        }
    }
    qDebug() << "returning false";
    return false;
}

void Handlefiles::copyFile(QString from, QString to) {
    QFile::remove(to + ".encrypted");
    QFileInfo fInfo(from);
    QFileInfo fInfoTo(to);

    encryptAndCopy(from, to, fInfo.fileName(), fInfoTo.absolutePath());
}

