#include "stackedwindow.h"
#include "ui_stackedwindow.h"

StackedWindow::StackedWindow(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::StackedWindow)
{
    ui->setupUi(this);



    connect (ui->pushManage, SIGNAL(clicked(bool)), SLOT(pushManageClicked()));
    connect (ui->pushSettings, SIGNAL(clicked(bool)), SLOT(pushSettingsClicked()));
    connect (ui->pushZurueckManage, SIGNAL(clicked(bool)), SLOT(pushZurueckManageClicked()));
    connect (ui->pushZurueckSettings, SIGNAL(clicked(bool)), SLOT(pushZurueckSettingsClicked()));

    connect (ui->pushDropbox, SIGNAL(clicked(bool)), SLOT(pushDropboxClicked()));
    connect (ui->pushICloud, SIGNAL(clicked(bool)), SLOT(pushICloudClicked()));
    connect (ui->pushZurueckDropbox, SIGNAL(clicked(bool)), SLOT(pushZurueckDropboxClicked()));
    connect (ui->pushZurueckICloud, SIGNAL(clicked(bool)), SLOT(pushZurueckICloudClicked()));

    connect (ui->pushAdd, SIGNAL(clicked(bool)), SLOT(pushAddClicked()));
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















