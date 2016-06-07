
#include "steerer.h"
#include "ui_steerer.h"
#include "window.h"
#include "filewindow.h"
#include "settingsmanager.h"
#include <QApplication>
#include <QProcess>

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
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayLeftClick(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();
    if (checkSettings()) {
        startAutoSync();
    }
}


void Steerer::createActions()
{
    settingsAction = new QAction(tr("&Open"), this);
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettings()));
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    openAction = new QAction(tr("Workdir"), this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFileWindow()));
    logoutAction = new QAction(tr("Logout"),this);
    connect(logoutAction, SIGNAL(triggered()),this, SLOT(logout()));


}

void Steerer::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(openAction);
    trayIconMenu->addAction(settingsAction);
    trayIconMenu->addAction(logoutAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon = new QSystemTrayIcon(this);
    QIcon icon(":/icons/images/icon_rund.png");
    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayIconMenu);
}

void Steerer::showSettings()
{
    Window::GetInstance().show();
    Window::GetInstance().raise();
    Window::GetInstance().activateWindow();
    if (Window::GetInstance().isMinimized()) {
        Window::GetInstance().showNormal();
    }
}

void Steerer::openFileWindow()
{
    FileWindow::GetInstance().show();
    FileWindow::GetInstance().raise();
    FileWindow::GetInstance().activateWindow();
    if (FileWindow::GetInstance().isMinimized()) {
        FileWindow::GetInstance().showNormal();
    }

}

void Steerer::logout()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    //login::GetInstance().show();


}

void Steerer::trayLeftClick(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        FileWindow::GetInstance().show();
        FileWindow::GetInstance().raise();
        FileWindow::GetInstance().activateWindow();
        if (FileWindow::GetInstance().isMinimized()) {
            FileWindow::GetInstance().showNormal();
        }
    }

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
