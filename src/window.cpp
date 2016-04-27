#include "window.h"
#include "ui_window.h"


Window::Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);



     //Verbinde Ereignis mit Methode
     connect (ui->pushHome, SIGNAL(clicked(bool)), SLOT(on_pushHome_clicked()));
     connect (ui->pushCloudService, SIGNAL(clicked(bool)), SLOT(on_pushCloudService_clicked()));
     connect (ui->pushManageCloud, SIGNAL(clicked(bool)), SLOT(on_pushManageCloud_clicked()));
     connect (ui->pushCPULimitation, SIGNAL(clicked(bool)), SLOT(on_pushCPULimitation_clicked()));
     connect (ui->pushChangePassword, SIGNAL(clicked(bool)), SLOT(on_pushChangePassword_clicked()));

     initializeFileBrowser();
     initializeTableWidget();
}

Window::~Window()
{
    delete ui;
}


void Window::on_pushHome_clicked()
{
    ui->Home->show();
    ui->CloudService->hide();
    ui->ManageCloud->hide();
    ui->CPULimitation->hide();
    ui->ChangePasword->hide();
}
void Window::on_pushCloudService_clicked()
{
    ui->CloudService->show();
    ui->Home->hide();
    ui->ManageCloud->hide();
    ui->CPULimitation->hide();
    ui->ChangePasword->hide();
}

void Window::on_pushManageCloud_clicked()
{
    ui->ManageCloud->show();
    ui->Home->hide();
    ui->CloudService->hide();
    ui->CPULimitation->hide();
    ui->ChangePasword->hide();
}

void Window::on_pushCPULimitation_clicked()
{
    ui->CPULimitation->show();
    ui->Home->hide();
    ui->CloudService->hide();
    ui->ManageCloud->hide();
    ui->ChangePasword->hide();
}

void Window::on_pushChangePassword_clicked()
{
    ui->ChangePasword->show();
    ui->Home->hide();
    ui->CloudService->hide();
    ui->ManageCloud->hide();
    ui->CPULimitation->hide();
}

void Window::on_pushButton_addDir_clicked()
{
    QString sPath = fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).absolutePath() + "/" + fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).baseName();
    //saveDirectories();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).absolutePath()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).baseName()));
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

void Window::initializeFileBrowser()
{
    QString sPath = "C:/";
    fileBrowserModel = new QFileSystemModel (this);
    fileBrowserModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    fileBrowserModel->setRootPath(sPath);


    ui->treeView_fileBrowser->setModel(fileBrowserModel);
    ui->treeView_fileBrowser->setColumnWidth(0,300);
}

void Window::initializeTableWidget() {
    QStringList title;
    title << "Pfad" << "Name";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(title);
    ui->tableWidget->setColumnWidth(0, 300);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

