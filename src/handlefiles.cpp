#include "handlefiles.h"
#include "settingsmanager.h"
#include "mainwindow.h"
#include <QDebug>

Handlefiles::Handlefiles()
{

}

bool Handlefiles::copy_dir_recursive(QString fromDir, QString toDir)
{
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
            qDebug() << TAG << "copy_dir_recursive: File already exists";
            //Display Warning
            /*
            if (QFile::remove(to) == false)
            {
                return false;
            }
            */
            return false;
        }

        if (QFile::copy(from, to) == false)
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
        if (copy_dir_recursive(from, to) == false)
        {
            return false;
        }
    }

    return true;
}


void Handlefiles::createCopyAndWorkDir() {
    Settingsmanager *setman = new Settingsmanager();
    QStringList keys = setman->loadSettings(MainWindow::settingsKeyForSaveDirPath);
    QString setting = setman->returnSetting(MainWindow::settingsKeyForSaveDirPath, keys[0]);
    QDir dir = QDir::root();
    if (!QDir(setting + "/MiniLockSync").exists()) {
        qDebug() << TAG << "createCopyAndWorkDir: MiniLockSync Ordner erstellt? " <<
        dir.mkpath(setting + "/MiniLockSync");
        setman->saveSettings(MainWindow::settingsKeyForSaveDirPath, "mainfolder", setting + "/MiniLockSync");
        setting += "/MiniLockSync";

        if (!QDir(setting + "/Workplace").exists()) {
            qDebug() << TAG << "createCopyAndWorkDir: Workplace Ordner erstellt? " <<
            dir.mkpath(setting + "/Workplace");
            setman->saveSettings(MainWindow::settingsKeyForSaveDirPath, "workplace", setting + "/Workplace");
        }

        if (!QDir(setting + "/Safetycopy").exists()) {
            qDebug() << TAG << "createCopyAndWorkDir: Safetycopy Ordner erstellt? " <<
            dir.mkpath(setting + "/Safetycopy");
            setman->saveSettings(MainWindow::settingsKeyForSaveDirPath, "safetycopy", setting + "/Safetycopy");
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
}
