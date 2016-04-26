#include "watcher.h"
#include <QString>
#include <QDebug>

Watcher::Watcher()
{

}

void Watcher::showModified(const QString &str)
{
    qDebug() << "Watcher showModified" << str;
}
