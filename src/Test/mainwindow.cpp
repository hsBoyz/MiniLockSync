#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filewindow.h"
#include <QtGui>
#include <QAction>
#include <QDebug>


QString MainWindow::settingsKeyForPaths = "directory";
QString MainWindow::settingsKeyForSaveDir = "savedir";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Einstellungen");

    settingsManager = new Settingsmanager();
    filesHandler = new HandleFiles();
    initializeLists();
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
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->tableWidget_saveDir->setColumnCount(2);
    ui->tableWidget_saveDir->setHorizontalHeaderLabels(title);
    ui->tableWidget_saveDir->setColumnWidth(0, 300);
    ui->tableWidget_saveDir->horizontalHeader()->setStretchLastSection(true);

    if (!settingsManager->loadSettings(settingsKeyForPaths).isEmpty()) {
        QStringList keys = settingsManager->loadSettings(settingsKeyForPaths);
        foreach (QString key, keys) {
            QDir dir = (settingsManager->returnSetting(settingsKeyForPaths, key));
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(dir.absolutePath()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(dir.dirName()));
        }
    }

    if (!settingsManager->loadSettings(settingsKeyForSaveDir).isEmpty()) {
        QStringList keys = settingsManager->loadSettings(settingsKeyForSaveDir);
        foreach (QString key, keys) {
            QDir dir = (settingsManager->returnSetting(settingsKeyForSaveDir, key));
            ui->tableWidget_saveDir->insertRow(ui->tableWidget_saveDir->rowCount());
            ui->tableWidget_saveDir->setItem(ui->tableWidget_saveDir->rowCount()-1, 0, new QTableWidgetItem(dir.absolutePath()));
            ui->tableWidget_saveDir->setItem(ui->tableWidget_saveDir->rowCount()-1, 1, new QTableWidgetItem(dir.dirName()));
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


/*
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}
*/

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();
    //ui->listWidget->addItem(sPath);
}

void MainWindow::on_pushButton_dir_clicked()
{
    QString sPath = dirmodel->fileInfo(ui->treeView->currentIndex()).absolutePath() + "/" + dirmodel->fileInfo(ui->treeView->currentIndex()).baseName();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(dirmodel->fileInfo(ui->treeView->currentIndex()).absolutePath()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(dirmodel->fileInfo(ui->treeView->currentIndex()).baseName()));

}


void MainWindow::on_pushButton_saveDir_clicked()
{
    QString sPath = dirmodel->fileInfo(ui->treeView->currentIndex()).absolutePath() + "/" + dirmodel->fileInfo(ui->treeView->currentIndex()).baseName();
    ui->tableWidget_saveDir->insertRow(ui->tableWidget_saveDir->rowCount());
    ui->tableWidget_saveDir->setItem(ui->tableWidget_saveDir->rowCount()-1, 0, new QTableWidgetItem(dirmodel->fileInfo(ui->treeView->currentIndex()).absolutePath()));
    ui->tableWidget_saveDir->setItem(ui->tableWidget_saveDir->rowCount()-1, 1, new QTableWidgetItem(dirmodel->fileInfo(ui->treeView->currentIndex()).baseName()));

    qDebug() << TAG << "saveDir path: " << sPath;

}


void MainWindow::on_btn_ok_dir_clicked()
{
    int rowCount = ui->tableWidget->rowCount();

    for (int i = 0; i < rowCount; i++) {
        QString path, name;
        path = ui->tableWidget->item(i, 0)->text();
        name = ui->tableWidget->item(i, 1)->text();

        //Adding name for getting the full path including selected folder
        if (!settingsManager->keyExists(settingsKeyForPaths, name)) {
            qDebug() << TAG + " ok_dir_clicked if";
            settingsManager->saveSettings(settingsKeyForPaths, name, path + "/" + name);
        }
    }

    QString path, name;
    path = ui->tableWidget_saveDir->item(0, 0)->text();
    name = ui->tableWidget_saveDir->item(0, 1)->text();

    if (!settingsManager->keyExists(settingsKeyForSaveDir, name)) {
        settingsManager->saveSettings(settingsKeyForSaveDir, name, path + "/" + name);
    }




    filesHandler->createCopyAndWorkDir();
    copyDirectory();

    fileWindow = new FileWindow(this);
    fileWindow->show();

    this->hide();
}


void MainWindow::copyDirectory(){

    QString from = settingsManager->returnSetting(MainWindow::settingsKeyForPaths, settingsManager->getKeyAtPosition(MainWindow::settingsKeyForPaths, 0));
    QString to = settingsManager->returnSetting(MainWindow::settingsKeyForSaveDir, "workplace");
    qDebug() << TAG << "copyDirectory from: " << from;
    qDebug() << TAG << "copyDirectory to: " << to;
    filesHandler->copy_dir_recursive(from, to);

    to = settingsManager->returnSetting(MainWindow::settingsKeyForSaveDir, "safetycopy");
    filesHandler->copy_dir_recursive(from, to);
}

