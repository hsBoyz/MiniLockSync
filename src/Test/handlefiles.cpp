#include "handlefiles.h"
#include <QDir>
#include <QFile>
#include <QString>
#include <QDebug>


HandleFiles::HandleFiles()
{

}

bool HandleFiles::copy_dir_recursive(QString fromDir, QString toDir)
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
