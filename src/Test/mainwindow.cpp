#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filewindow.h"
#include <QtGui>
#include <QAction>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Einstellungen");

    settingsManager = new Settingsmanager();
    initializeLists();
    createActions();
    createTrayIcon();
    trayIcon->show();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeLists() {
    QString sPath = "C:/";
    dirmodel = new QFileSystemModel (this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(sPath);


    ui->treeView->setModel(dirmodel);
    ui->treeView->setColumnWidth(0,300);


    QStringList title;
    title << "Pfad" << "Name";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(title);
    ui->tableWidget->setColumnWidth(0, 300);

    if (!settingsManager->loadSettings("directory").isEmpty()) {
        QStringList keys = settingsManager->loadSettings("directory");
        foreach (QString key, keys) {
            QDir dir = (settingsManager->returnSetting("directory", key));
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(dir.absolutePath()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(dir.dirName()));
        }
    }


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


void MainWindow::on_pushButton_saveDir_clicked()
{
    QString sPath = dirmodel->fileInfo(ui->treeView->currentIndex()).absolutePath() + "/" + dirmodel->fileInfo(ui->treeView->currentIndex()).baseName();
    ui->tableWidget_saveDir->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget_saveDir->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(dirmodel->fileInfo(ui->treeView->currentIndex()).absolutePath()));
    ui->tableWidget_saveDir->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(dirmodel->fileInfo(ui->treeView->currentIndex()).baseName()));

}


void MainWindow::on_btn_ok_dir_clicked()
{
    int rowCount = ui->tableWidget->rowCount();
    for (int i = 0; i < rowCount; i++) {
        QString path, name;
        path = ui->tableWidget->item(i, 0)->text();
        name = ui->tableWidget->item(i, 1)->text();

        //Adding name for getting the full path including selected folder
        if (!settingsManager->keyExists("directory", name)) {
            qDebug() << TAG + " ok_dir_clicked if";
            settingsManager->saveSettings("directory", name, path + "/" + name);
        }

    }

    fileWindow = new FileWindow(this);
    fileWindow->show();
    //this->hide();
}
