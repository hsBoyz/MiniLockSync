#include "settingsmanager.h"
#include <QSettings>
#include <QDebug>
#include <QDir>


Settingsmanager::Settingsmanager()
{

}

void Settingsmanager::saveSettings(QString group, QString key, QString value) {
    QSettings setting(myApp, mySetting);
    setting.beginGroup(group);
    setting.setValue(key, value);

    setting.endGroup();

    qDebug() << TAG + " saveSettings: " + "saved";
}

QStringList Settingsmanager::loadSettings(QString group) {
    QSettings setting(myApp, mySetting);
    QStringList keys;

    setting.beginGroup(group);
    keys = setting.allKeys();
    setting.endGroup();

    return keys;
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

    qDebug() << TAG + "removeKey: Key " + keyToRemove + " removed";

    if (setting.allKeys().length() == 0){
        setting.remove("");
        qDebug() << TAG + ": Group " + group + " removed";
    }

    setting.endGroup();
}

/*
void Settingsmanager::printGroups() {
    QSettings setting(myApp, mySetting);
    QStringList list = setting.childGroups();

    foreach(QString grp, list) {
        qDebug() << grp;
        setting.beginGroup(grp);
        QStringList keyList = setting.allKeys();
        foreach(QString key, keyList) {
            qDebug() << TAG + " printGroups: " + key;
            //this->removeKey(grp, key);
        }
        setting.endGroup();
    }
}
*/

void Settingsmanager::removeAllKeys() {
    QSettings setting(myApp, mySetting);
    QStringList list = setting.childGroups();

    foreach(QString grp, list) {
        qDebug() << grp;
        setting.beginGroup(grp);
        QStringList keyList = setting.allKeys();
        foreach(QString key, keyList) {
            qDebug() << TAG + " " + key;
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

bool Settingsmanager::keyExists(QString group, QString key) {
    QSettings setting(myApp, mySetting);
    setting.beginGroup(group);
    if (setting.contains(key)){
        setting.endGroup();
        return true;
    }
    else {
        setting.endGroup();
        return false;
    }
}
