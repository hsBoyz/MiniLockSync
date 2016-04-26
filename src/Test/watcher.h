#ifndef WATCHER_H
#define WATCHER_H

#include "settingsmanager.h"
#include <QFileSystemWatcher>

class Watcher : public QObject
{
    Q_OBJECT

public:
    Watcher();



public slots:
    void showModified(const QString &str);

};

#endif // WATCHER_H
