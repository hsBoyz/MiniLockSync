#include "filewindow.h"
#include "ui_filewindow.h"



FileWindow::FileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);

    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);

    ui->listView->setModel(filemodel);

    setman = new Settingsmanager();

}

FileWindow::~FileWindow()
{
    delete ui;
}

void FileWindow::on_pushButton_clicked()
{
    //save
    setman->saveSettings();
}

void FileWindow::on_pushButton_2_clicked()
{
    //load
    setman->loadSettings();
}
