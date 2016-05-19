
#include "steerer.h"
#include "ui_steerer.h"
#include "window.h"
#include "filewindow.h"
#include "settingsmanager.h"

#include <QMessageBox>

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
    if (checkSettings()) {
        startAutoSync();
    }
}


void Steerer::createActions()
{
    settingsAction = new QAction(tr("&Settings"), this);
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettings()));
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    openAction = new QAction(tr("Open"), this);
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
    QIcon icon(":/icons/images/MiniLock_15x15.png");
    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayIconMenu);
}

void Steerer::showSettings()
{
    Window *w = new Window();
    w->show();

}

void Steerer::openFileWindow()
{
    FileWindow *f = new FileWindow();
    f->show();
}

bool Steerer::checkSettings() {
    Settingsmanager *setman = new Settingsmanager();
    if (setman->groupExists(MainWindow::settingsKeyForPaths) &&
            setman->groupExists(MainWindow::settingsKeyForCloudDirPath) &&
                  setman->groupExists(MainWindow::settingsKeyForWorkDirPath)) {
        return true;
    }
    else {
        return false;
    }
}

void Steerer::startAutoSync() {
   Timer::GetInstance().start();
}
