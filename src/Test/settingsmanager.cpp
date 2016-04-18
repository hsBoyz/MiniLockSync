#include "settingsmanager.h"
#include <QSettings>
#include <QDebug>

Settingsmanager::Settingsmanager()
{
    qDebug() << "Ctor erstellt";
}

void Settingsmanager::saveSettings(QString group, QString key, QString value) {
    QSettings setting(myApp, mySetting);
    setting.beginGroup(group);
    setting.setValue(key, value);

    setting.endGroup();

    qDebug() << "saved";
}


void Settingsmanager::loadSettings(QString group, QString key) {
    QSettings setting(myApp, mySetting);
    setting.beginGroup(group);


    qDebug() << setting.value(key).toString();

    setting.endGroup();
}

QString Settingsmanager::returnSetting(QString group, QString key) {
    QSettings setting(myApp, mySetting);
    QString value;
    setting.beginGroup(group);
    value = setting.value(key).toString();
    setting.endGroup();

    return value;
}

void Settingsmanager::removeKey(QString group, QString keyToRemove) {
    QSettings setting(myApp, mySetting);
    setting.beginGroup(group);
    setting.remove(keyToRemove);

    if (setting.allKeys().length() == 0){
        setting.remove("");
        qDebug() << "Group " + group + " removed";
    }

    setting.endGroup();
}

void Settingsmanager::printGroups() {
    QSettings setting(myApp, mySetting);
    QStringList list = setting.childGroups();

    foreach(QString grp, list) {
        qDebug() << grp;
        setting.beginGroup(grp);
        QStringList keyList = setting.allKeys();
        foreach(QString key, keyList) {
            qDebug() << key;
            //this->removeKey(grp, key);
        }
        setting.endGroup();
    }
}

void Settingsmanager::removeAllKeys() {
    QSettings setting(myApp, mySetting);
    QStringList list = setting.childGroups();

    foreach(QString grp, list) {
        qDebug() << grp;
        setting.beginGroup(grp);
        QStringList keyList = setting.allKeys();
        foreach(QString key, keyList) {
            qDebug() << key;
            this->removeKey(grp, key);
        }
        setting.endGroup();
    }
}

QString Settingsmanager::getKeyAtPosition(QString group, int position) {
    QSettings setting(myApp, mySetting);
    setting.beginGroup(group);
    QStringList keyList = setting.allKeys();
    setting.endGroup();

    return keyList[position];
}
