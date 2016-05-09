#ifndef HANDLEFILES_H
#define HANDLEFILES_H
#include "settingsmanager.h"
#include <QString>

class Handlefiles
{
public:
    Handlefiles();
    QString TAG = "HANDLEFILES ";



    bool copy_dir_recursive(QString fromDir, QString toDir);
    bool delete_dir_recursive(QString dirDelete);
    void createCopyAndWorkDir(QString group);
    QString createDir(QString path, QString folderName);
};

#endif // HANDLEFILES_H
