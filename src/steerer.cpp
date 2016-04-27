#include "steerer.h"
#include "ui_steerer.h"
#include "ui_stackedwindow.h"
//#include "stackedwindow.h"

Steerer::Steerer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Steerer)
{
    ui->setupUi(this);
    stackedwin = new StackedWindow();
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
    QIcon icon(":/icons/images/MiniLock_15x15.png");
    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayIconMenu);
}

void Steerer::showSettings()
{
    //MainWindow *w = new MainWindow();
    //w->show();

    //stackedwin->show();
    //stackedwin->ui->Settings->show();
    stackedwin->show();
    stackedwin->pushSettingsClicked();
}

void Steerer::openFileWindow()
{
    stackedwin->show();
    stackedwin->pushManageClicked();
}