#ifndef HANDLEFILES_H
#define HANDLEFILES_H
#include "QString"


class HandleFiles
{
public:
    HandleFiles();
    ~HandleFiles();

    bool copy_dir_recursive(QString fromDir, QString toDir);
    void createCopyAndWorkDir();

private:
    QString TAG = "HANDLEFILES ";

};

#endif // HANDLEFILES_H
