#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QDir>


class Settingsmanager
{
private:
    QString TAG = "SETTINGSMANAGER";
    QString myApp = "MyApp";
    QString mySetting = "MySetting";
public:
    Settingsmanager();
    ~Settingsmanager();
    void saveSettings(QString group, QString key, QString value);
    QStringList loadSettings(QString group);
    QString returnSetting(QString group, QString key);
    void removeKey(QString group, QString keyToRemove);
    QString getKeyAtPosition(QString group, int position);
    //void removeAllKeys();
    //void printGroups();
    bool keyExists(QString group, QString key);
};

#endif // SETTINGSMANAGER_H
