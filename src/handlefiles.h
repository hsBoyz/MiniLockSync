#ifndef HANDLEFILES_H
#define HANDLEFILES_H
#include "settingsmanager.h"
#include "login.hpp"
#include <uCryptLib.h>
#include <QString>
#include <QThread>


class Handlefiles
{

public:
    Handlefiles();
    QString TAG = "HANDLEFILES ";

    bool copy_dir_recursive(QString fromDir, QString toDir, bool encryptionOn);
    bool copy_dir_recursive_cloud(QString fromDir, QString toDir);
    bool delete_dir_recursive(QString dirDelete);
    void createCopyAndWorkDir(QString group);
    QString createDir(QString path, QString folderName);
    void checkForErrors(int result);
    void copyDirectory();
    void copyEncryptedFromCloud();
    void copyFile(QString from, QString to);
    void checkAndCopyWorkDir();

private:
     login *log;
     Settingsmanager *settingsmanager;

     bool encryptAndCopy(QString from, QString to, QString copyfile, QString toDir);
     bool decryptAndCopy(QString from, QString to, QString copyfile, QString toDir);
     bool checkListForEncryptedFiles(QFileInfoList list);


};

#endif // HANDLEFILES_H
