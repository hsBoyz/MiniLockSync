#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filewindow.h"
#include <QtGui>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Einstellungen");


    createActions();
    createTrayIcon();
    trayIcon->show();


    QString sPath = "C:/";
    dirmodel = new QFileSystemModel (this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(sPath);

    ui->treeView->setModel(dirmodel);

    QStringList title;
    title << "Pfad" << "Name";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(title);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent * evt) {
    switch(evt->type())
    {
        case QEvent::LanguageChange :
            this->ui->retranslateUi(this);
            break;
        case QEvent::WindowStateChange:
        {
            if (isMinimized()) {
                this->hide();
            }
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}

void MainWindow::createActions()
{
    restoreAction = new QAction(tr("&Einstellungen"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    quitAction = new QAction(tr("&Beenden"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon = new QSystemTrayIcon(this);
    QIcon icon(":/icon/MiniLock_15x15.png");
    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayIconMenu);
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();
    //ui->listWidget->addItem(sPath);
}

void MainWindow::on_pushButton_clicked()
{
    QString sPath = dirmodel->fileInfo(ui->treeView->currentIndex()).absolutePath() + "/" + dirmodel->fileInfo(ui->treeView->currentIndex()).baseName();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(dirmodel->fileInfo(ui->treeView->currentIndex()).absolutePath()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(dirmodel->fileInfo(ui->treeView->currentIndex()).baseName()));

}


void MainWindow::on_btn_ok_dir_clicked()
{
    fileWindow = new FileWindow(this);
    fileWindow->show();
    //this->hide();
    //ui->tableWidget->
}
