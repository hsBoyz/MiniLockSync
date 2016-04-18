#include "settingsmanager.h"
#include <QSettings>
#include <QDebug>

Settingsmanager::Settingsmanager()
{
    qDebug() << "Ctor erstellt";
}

void Settingsmanager::loadSettings() {
    QSettings setting("MyApp", "MySetting");
    setting.beginGroup("Mainwindow");

    qDebug() << setting.value("speicherort").toString();

    setting.endGroup();
}

void Settingsmanager::saveSettings() {
    QSettings setting("MyApp", "MySetting");
    setting.beginGroup("Mainwindow");
    setting.setValue("speicherort", "pfad1");

    setting.endGroup();

    qDebug() << "saved";
}
