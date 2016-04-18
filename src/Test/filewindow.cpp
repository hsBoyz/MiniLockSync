#include "filewindow.h"
#include "ui_filewindow.h"

#include <QDebug>



FileWindow::FileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);

    setman = new Settingsmanager();

    filemodel_1 = new QFileSystemModel(this);
    filemodel_1->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    QString sPath1 = setman->returnSetting("directory", setman->getKeyAtPosition("directory", 0));
    filemodel_1->setRootPath(sPath1);

    ui->listView->setModel(filemodel_1);
    ui->listView->setRootIndex(filemodel_1->index(sPath1));

    filemodel_2 = new QFileSystemModel(this);
    filemodel_2->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    QString sPath2 = setman->returnSetting("directory", setman->getKeyAtPosition("directory", 1));
    filemodel_2->setRootPath(sPath2);

    ui->listView_2->setModel(filemodel_2);
    ui->listView_2->setRootIndex(filemodel_2->index(sPath2));
}

FileWindow::~FileWindow()
{
    delete ui;
}

void FileWindow::on_pushButton_clicked()
{
    //save
    setman->saveSettings("Test", "key", "value");
}

void FileWindow::on_pushButton_2_clicked()
{
    //load
    setman->loadSettings("Test", "key");
}

void FileWindow::on_pushButton_3_clicked()
{
    setman->removeAllKeys();
}

void FileWindow::on_pushButton_4_clicked()
{
    setman->printGroups();
}
