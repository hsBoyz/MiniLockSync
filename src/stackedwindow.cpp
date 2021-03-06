#include "stackedwindow.h"
#include "ui_stackedwindow.h"
#include "mainwindow.h"

#include <QtGui>

StackedWindow::StackedWindow(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::StackedWindow)
{
    ui->setupUi(this);
    settingsmanager = new Settingsmanager();


    connect (ui->pushManage, SIGNAL(clicked(bool)), SLOT(pushManageClicked()));
    connect (ui->pushSettings, SIGNAL(clicked(bool)), SLOT(pushSettingsClicked()));
    connect (ui->pushZurueckManage, SIGNAL(clicked(bool)), SLOT(pushZurueckManageClicked()));
    connect (ui->pushZurueckSettings, SIGNAL(clicked(bool)), SLOT(pushZurueckSettingsClicked()));

    connect (ui->pushDropbox, SIGNAL(clicked(bool)), SLOT(pushDropboxClicked()));
    connect (ui->pushICloud, SIGNAL(clicked(bool)), SLOT(pushICloudClicked()));
    connect (ui->pushZurueckDropbox, SIGNAL(clicked(bool)), SLOT(pushZurueckDropboxClicked()));
    connect (ui->pushZurueckICloud, SIGNAL(clicked(bool)), SLOT(pushZurueckICloudClicked()));

    connect (ui->pushAdd, SIGNAL(clicked(bool)), SLOT(pushAddClicked()));


    initializeFileBrowser();
    initializeTableWidget();
    populateTableWidget();
}

StackedWindow::~StackedWindow()
{
    delete ui;
}

/*
 *
 *
 *
 * Button slot functions
 *
 *
 *
 */

void StackedWindow::pushManageClicked(){
    ui->Manage->show();

    ui->Main->hide();
}

void StackedWindow::pushSettingsClicked(){
    ui->Settings->show();
    ui->Main->hide();
}

void StackedWindow::pushZurueckManageClicked(){
    ui->Main->show();
    ui->Manage->hide();
}

void StackedWindow::pushZurueckSettingsClicked(){
    ui->Main->show();
    ui->Settings->hide();
}

void StackedWindow::pushDropboxClicked(){
    ui->Dropbox->show();
    ui->Manage->hide();
}

void StackedWindow::pushICloudClicked(){
    ui->ICloud->show();
    ui->Manage->hide();
}

void StackedWindow::pushZurueckDropboxClicked(){
    ui->Manage->show();
    ui->Dropbox->hide();
}

void StackedWindow::pushZurueckICloudClicked(){
    ui->Manage->show();
    ui->ICloud->hide();
}

void StackedWindow::pushAddClicked()
{
    ui->AddCloud->show();
    ui->Settings->hide();
}

void StackedWindow::on_pushButton_addDir_clicked()
{
    QString sPath;
    QString name;
    if (fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).baseName().length() != 0){
        sPath = fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).absolutePath() + "/" + fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).baseName();
        name = fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).baseName();
    }
    else {
        sPath = fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).absolutePath();
        name = "noName";
    }
    saveDirectories(name, sPath);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).absolutePath()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).baseName()));
}

void StackedWindow::on_pushButton_deleteDir_clicked()
{
    QItemSelectionModel *select = ui->tableWidget->selectionModel();
    QModelIndexList indexList = select->selectedIndexes();

    foreach (QModelIndex index, indexList) {
        int row = index.row();
        QString name = ui->tableWidget->item(row, 1)->text();

        settingsmanager->removeKey(MainWindow::settingsKeyForPaths, name);
        ui->tableWidget->removeRow(row);
    }

}

/*
 *
 *
 *
 *General functions
 *
 *
 *
 */

void StackedWindow::initializeFileBrowser()
{
    QString sPath = "C:/";
    fileBrowserModel = new QFileSystemModel (this);
    fileBrowserModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    fileBrowserModel->setRootPath(sPath);


    ui->treeView_fileBrowser->setModel(fileBrowserModel);
    ui->treeView_fileBrowser->setColumnWidth(0,300);
}

void StackedWindow::initializeTableWidget() {
    QStringList title;
    title << "Pfad" << "Name";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(title);
    ui->tableWidget->setColumnWidth(0, 300);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

void StackedWindow::saveDirectories(QString name, QString path) {
    //Adding name for getting the full path including selected folder
    if (!settingsmanager->keyExists(MainWindow::settingsKeyForPaths, name)) {
       settingsmanager->saveSettings(MainWindow::settingsKeyForPaths, name, path);
    }
}

void StackedWindow::populateTableWidget() {
    if (!settingsmanager->loadSettings(MainWindow::settingsKeyForPaths).isEmpty()) {
        QStringList keys = settingsmanager->loadSettings(MainWindow::settingsKeyForPaths);
        foreach (QString key, keys) {
            QDir dir = (settingsmanager->returnSetting(MainWindow::settingsKeyForPaths, key));
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(dir.absolutePath()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(dir.dirName()));
        }
    }
}

void StackedWindow::deleteDirectories(QString name) {
    if (settingsmanager->keyExists(MainWindow::settingsKeyForPaths, name)) {
        settingsmanager->removeKey(MainWindow::settingsKeyForPaths, name);
    }
}


















