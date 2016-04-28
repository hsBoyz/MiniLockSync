#ifndef HANDLEFILES_H
#define HANDLEFILES_H
#include <QString>

class Handlefiles
{
public:
    Handlefiles();
    QString TAG = "HANDLEFILES ";

    bool copy_dir_recursive(QString fromDir, QString toDir);
    void createCopyAndWorkDir();
};

#endif // HANDLEFILES_H
