#include "steerer.h"
#include "ui_steerer.h"
#include "mainwindow.h"
#include "filewindow.h"
#include "watcher.h"
#include <QDebug>
#include <QFileSystemWatcher>

Steerer::Steerer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Steerer)
{
    ui->setupUi(this);

}

Steerer::~Steerer()
{
    delete ui;
}

void Steerer::start()
{
    createActions();
    createTrayIcon();
    trayIcon->show();

}


void Steerer::createActions()
{
    settingsAction = new QAction(tr("&Einstellungen"), this);
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettings()));
    quitAction = new QAction(tr("&Beenden"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    openAction = new QAction(tr("Öffnen"), this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFileWindow()));
}

void Steerer::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(openAction);
    trayIconMenu->addAction(settingsAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon = new QSystemTrayIcon(this);
    QIcon icon(":/icon/MiniLock_15x15.png");
    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayIconMenu);
}

void Steerer::showSettings()
{
    MainWindow *w = new MainWindow();
    w->show();
}

void Steerer::openFileWindow()
{
    FileWindow *w = new FileWindow();
    w->show();
}
