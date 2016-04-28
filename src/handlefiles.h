#ifndef HANDLEFILES_H
#define HANDLEFILES_H


class Handlefiles
{
public:
    Handlefiles();

    bool copy_dir_recursive(QString fromDir, QString toDir);
    void createCopyAndWorkDir();
};

#endif // HANDLEFILES_H
