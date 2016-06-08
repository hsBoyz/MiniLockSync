#include "settingsmanager.h"
#include <QSettings>
#include <QDebug>
#include <QDir>


Settingsmanager::Settingsmanager()
{

}

void Settingsmanager::saveSettings(QString group, QString key, QString value) {
    /*QSettings setting(myApp, mySetting);
    //setting.beginGroup(group);
    setting.setValue(login::user + "/" + key, value);

    //setting.endGroup();

    qDebug() << TAG + " saveSettings: " + "saved key/value: " << login::user + "/" + key, value;
    */

    QSettings setting(myApp, mySetting);
    setting.beginGroup(login::user);
    setting.beginGroup(group);
    setting.setValue(key, value);
    setting.endGroup(); //group
    setting.endGroup(); //login.user

    qDebug() << TAG + " saveSettings: user " << login::user + "saved key/value: " << key  << " " << value;
}

QStringList Settingsmanager::loadSettings(QString group) {
    qDebug() << TAG << " loadsettings: " << login::user;
    /*
    QSettings setting(myApp, mySetting);
    QStringList keysUser;
    QStringList keys;

    setting.beginGroup(group);
    keysUser = setting.childKeys();

    foreach (QString child, keysUser) {
        qDebug() << TAG << " loadsetting: childgroups: " << child;
    }
    */
    QSettings setting(myApp, mySetting);
    QStringList keys;

    setting.beginGroup(login::user);
    setting.beginGroup(group);
    keys = setting.childKeys();

    foreach (QString key, keys) {
        qDebug() << TAG << " loadsetting: " << "user: " << login::user << "key: " << key;
    }

    return keys;
}

QString Settingsmanager::returnSetting(QString group, QString key) {
    QSettings setting(myApp, mySetting);
    QString value;
    setting.beginGroup(login::user);
    setting.beginGroup(group);
    value = setting.value(key).toString();
    setting.endGroup(); //group
    setting.endGroup(); //login::user

    return value;
}

void Settingsmanager::removeKey(QString group, QString keyToRemove) {
    QSettings setting(myApp, mySetting);
    setting.beginGroup(login::user);
    setting.beginGroup(group);
    setting.remove(keyToRemove);

    qDebug() << TAG + "removeKey: Key " + keyToRemove + " removed";

    if (setting.allKeys().length() == 0){
        setting.remove("");
        qDebug() << TAG + ": Group " + login::user + "/" +  group + " removed";
    }

    setting.endGroup(); //group
    setting.endGroup(); //login::user
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
    /*
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
    */
    QSettings setting(myApp, mySetting);
    QStringList allKeys = setting.allKeys();
    foreach (QString key, allKeys) {
        setting.remove(key);
        qDebug() << TAG << " removeAllKey: removed key: " << key;
    }


}


QString Settingsmanager::getKeyAtPosition(QString group, int position) {
    QSettings setting(myApp, mySetting);
    setting.beginGroup(login::user);
    setting.beginGroup(group);
    QStringList keyList = setting.allKeys();
    setting.endGroup(); //group
    setting.endGroup(); //login::user

    return keyList[position];
}

bool Settingsmanager::keyExists(QString group, QString key) {
    QSettings setting(myApp, mySetting);
    setting.beginGroup(login::user);
    setting.beginGroup(group);
    if (setting.contains(key)){
        setting.endGroup(); //group
        setting.endGroup(); //login::user
        return true;
    }
    else {
        setting.endGroup(); //group
        setting.endGroup(); //login::user
        return false;
    }
}

bool Settingsmanager::groupExists(QString group) {
    QSettings setting(myApp, mySetting);
    setting.beginGroup(login::user);
    setting.beginGroup(group);
    QStringList list = setting.allKeys();
    if (list.length() != 0){
        setting.endGroup(); //group
        setting.endGroup(); //login::user
        return true;
    }
    else {
        setting.endGroup(); //group
        setting.endGroup(); //login::user
        return false;
    }
}

QString Settingsmanager::valueExists(QString value) {
    QSettings setting(myApp, mySetting);
    setting.beginGroup(login::user);
    QStringList list = setting.allKeys();
    foreach (QString key, list) {
        if (setting.value(key) == value) {
            setting.endGroup();
            return key;
        }
    }
    setting.endGroup();
    return "false";
}

