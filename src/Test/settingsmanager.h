#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>


class Settingsmanager
{
private:
    QString myApp = "MyApp";
    QString mySetting = "MySetting";
public:
    Settingsmanager();
    ~Settingsmanager();
    void saveSettings(QString group, QString key, QString value);
    void loadSettings(QString group, QString key);
    QString returnSetting(QString group, QString key);
    void removeKey(QString group, QString keyToRemove);
    QString getKeyAtPosition(QString group, int position);
    void removeAllKeys();
    void printGroups();
};

#endif // SETTINGSMANAGER_H
