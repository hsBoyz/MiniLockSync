#include "handlefiles.h"
#include "settingsmanager.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QObject>

Handlefiles::Handlefiles()
{
    log = new login();
    settingsmanager = new Settingsmanager();
}

bool Handlefiles::copy_dir_recursive(QString fromDir, QString toDir, bool encryptionOn)
{
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

            //qDebug() << TAG << "copy_dir_recursive, fromInfo: " << fromInfo.lastModified().date();
            //qDebug() << TAG << "copy_dir_recursive, toInfo: " << toInfo.lastModified().;

            if (fromInfo.lastModified().toMSecsSinceEpoch() > toInfo.lastModified().toMSecsSinceEpoch()) {
                qDebug() << TAG << "copy_dir_recursive, fromInfo: " << fromInfo.lastModified();
                qDebug() << TAG << "copy_dir_recursive, toInfo: " << toInfo.lastModified();

                if (encryptionOn) {
                    QFile::remove(to);
                    encryptAndCopy(from, to, copyfile, toDir);
                }
                else {
                QFile::remove(to);
                QFile::copy(from, to);
                }
            }

            /*
            msgBox.setInformativeText("File " + to + " already exists. Do you want to override it?");

            switch (msgBox.exec()) {
                case QMessageBox::Ok:
                    QFile::remove(to);
                    QFile::copy(from, to);
                    break;
                case QMessageBox::Cancel:
                    // Cancel was clicked
                    break;
                default:
                    // should never be reached
                    break;
              }
              */
            //Display Warning
            /*
            if (QFile::remove(to) == false)
            {
                return false;
            }
            */
            //return false;
        }

        if (encryptionOn) {
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

void Handlefiles::createCopyAndWorkDir(QString group) {

    /*
    *
    *Not necessary yet, because folders of workdir and safetycopydir
    *are choosen in settings before.
    *
    *This becomes necessary if the user wants to create new folders with
    * specific names at selected directory
    *
    *
    *
    *
    */

    /*
    Settingsmanager *setman = new Settingsmanager();
    QStringList keys = setman->loadSettings(group);

    foreach(QString key, keys) {
        QString setting = setman->returnSetting(group, key);
        QDir dir = QDir::root();


    }
    */

    /*

    if (!QDir(setting + "/MiniLockSync").exists()) {
        qDebug() << TAG << "createCopyAndWorkDir: MiniLockSync Ordner erstellt? " <<
        dir.mkpath(setting + "/MiniLockSync");
        setman->saveSettings(MainWindow::settingsKeyForSaveDir, "mainfolder", setting + "/MiniLockSync");
        setting += "/MiniLockSync";
            if (!QDir(setting + "/Workplace").exists()) {
                qDebug() << TAG << "createCopyAndWorkDir: Workplace Ordner erstellt? " <<
                dir.mkpath(setting + "/Workplace");
                setman->saveSettings(MainWindow::settingsKeyForSaveDir, "workplace", setting + "/Workplace");
            }

            if (!QDir(setting + "/Safetycopy").exists()) {
                qDebug() << TAG << "createCopyAndWorkDir: Safetycopy Ordner erstellt? " <<
                dir.mkpath(setting + "/Safetycopy");
                setman->saveSettings(MainWindow::settingsKeyForSaveDir, "safetycopy", setting + "/Safetycopy");
            }

    }

    }
    else if (QDir(setting + "/MiniLockSync").exists()){

        setting += "/MiniLockSync";

        if (!QDir(setting + "/Workplace").exists()) {
            //qDebug() << TAG << "createCopyAndWorkDir else: Workplace Ordner erstellt? " <<
            dir.mkpath(setting + "/Workplace");
            setman->saveSettings(MainWindow::settingsKeyForSaveDirPath, "workplace", setting + "/Workplace");
        }

        if (!QDir(setting + "/Safetycopy").exists()) {
            //qDebug() << TAG << "createCopyAndWorkDir else: Safetycopy Ordner erstellt? " <<
            dir.mkpath(setting + "/Safetycopy");
            setman->saveSettings(MainWindow::settingsKeyForSaveDirPath, "safetycopy", setting + "/Safetycopy");

        }

        if (!setman->keyExists(MainWindow::settingsKeyForSaveDirPath, "mainfolder")) {
            setman->saveSettings(MainWindow::settingsKeyForSaveDirPath, "mainfolder", setting + "/MiniLockSync");
        }
        if (!setman->keyExists(MainWindow::settingsKeyForSaveDirPath, "workplace")) {
            setman->saveSettings(MainWindow::settingsKeyForSaveDirPath, "workplace", setting + "/Workplace");
        }
        if (!setman->keyExists(MainWindow::settingsKeyForSaveDirPath, "safetycopy")) {
            setman->saveSettings(MainWindow::settingsKeyForSaveDirPath, "safetycopy", setting + "/Safetycopy");
        }
    }
    */
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
    }

}

bool Handlefiles::encryptAndCopy(QString from, QString to, QString copyfile, QString toDir) {
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
