#include "window.h"
#include "ui_window.h"
#include "filewindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QSignalMapper>
#include <QPalette>
Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

//----------------------------------------------------------
    // Das komplette Menü zum Hauptprogramm
        QMenu *fileMenu = new QMenu(tr("&File"), this);
        menuBar()->addMenu(fileMenu);
        act3 = fileMenu->addAction(
                    QIcon(":/icons/images/cancel.png")   ,
                    tr("Quit"),
           qApp, SLOT(quit()),
           QKeySequence(tr("Ctrl+Q", "File|Quit")) );
        act3->setStatusTip(tr("Quit Program"));
       /* QMenu *workMenu = new QMenu(
           tr("&Edit"), this);
        menuBar()->addMenu(workMenu); */
//--------------------------------------------------------

    settingsmanager = new Settingsmanager();
    filesHandler = new Handlefiles();

    //Verbinde Ereignis mit Methode
    connect (ui->pushHome, SIGNAL(clicked(bool)), this, SLOT(on_pushHome_clicked()));
    connect (ui->pushCloudService, SIGNAL(clicked(bool)), this, SLOT(on_pushCloudService_clicked()));
    connect (ui->pushManageCloud, SIGNAL(clicked(bool)), this, SLOT(on_pushManageCloud_clicked()));
    connect (ui->pushManageSaveDir, SIGNAL(clicked(bool)), this, SLOT(on_pushManageSaveDir_clicked()));
    //connect (ui->pushCPULimitation, SIGNAL(clicked(bool)), this, SLOT(on_pushCPULimitation_clicked()));
    //connect (ui->pushChangePassword, SIGNAL(clicked(bool)), this, SLOT(on_pushChangePassword_clicked()));



    initializeFileBrowser();
    initializeTableWidget(ui->tableWidget);
    initializeTableWidget(ui->tableWidget_dir);
    initializeTableWidget(ui->tableWidget_cloud);
    populateTableWidget(MainWindow::settingsKeyForPaths, ui->tableWidget);
    populateTableWidget(MainWindow::settingsKeyForWorkDirPath, ui->tableWidget_dir);
    populateTableWidget(MainWindow::settingsKeyForCloudDirPath, ui->tableWidget_cloud);

    /*
    QPalette greenPalette = ui->pushHome->palette();
    greenPalette.setColor(QPalette::Window, Qt::green);
    ui->pushHome->setPalette(QPalette(QColor(Qt::green)));
    */



}

Window::~Window()
{
    delete ui;
}
// Kontextmenü verwenden contextMenuEvent
// ist eine virtuelle Methode
/*
void Window::contextMenuEvent(
    QContextMenuEvent *event) {
   QMenu *menu = new QMenu(this);
   //menu->addAction(act1);
   //menu->addAction(act2);
   menu->addAction(act3);
   menu->exec(event->globalPos());
}
*/


/*
 *
 *
 *
 * Button slot functions
 *
 *
 *
 */

void Window::on_pushHome_clicked()
{
    FileWindow::GetInstance().hide();

    currentIndex = ui->stackedWidget->currentIndex();
          if( currentIndex < ui->stackedWidget->count())
          {
              ui->stackedWidget->setCurrentIndex(0); // Home

          }
}
void Window::on_pushCloudService_clicked()
{

    currentIndex = ui->stackedWidget->currentIndex();
          if( currentIndex < ui->stackedWidget->count())
          {
              ui->stackedWidget->setCurrentIndex(1); // CloudService

          }

          FileWindow::GetInstance().show();
          FileWindow::GetInstance().raise();
          FileWindow::GetInstance().activateWindow();

          if (FileWindow::GetInstance().isMinimized()){
              FileWindow::GetInstance().showNormal();

          }

}



void Window::on_pushManageCloud_clicked()
{
    FileWindow::GetInstance().hide();
    currentIndex = ui->stackedWidget->currentIndex();
          if( currentIndex < ui->stackedWidget->count())
          {
              ui->stackedWidget->setCurrentIndex(2); // Manage Cloud
          }
}

void Window::on_pushManageSaveDir_clicked()
{
    FileWindow::GetInstance().hide();
    currentIndex = ui->stackedWidget->currentIndex();
          if( currentIndex < ui->stackedWidget->count())
          {
              ui->stackedWidget->setCurrentIndex(3); // Manage Save Dir
          }
}
/*
void Window::on_pushCPULimitation_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
          if( currentIndex < ui->stackedWidget->count())
          {
              ui->stackedWidget->setCurrentIndex(4); // CPU Limitation
          }
}

void Window::on_pushChangePassword_clicked()
{
    currentIndex = ui->stackedWidget->currentIndex();
          if( currentIndex < ui->stackedWidget->count())
          {
              ui->stackedWidget->setCurrentIndex(5); // Change PW
          }
}
*/
void Window::on_pushButton_addDir_clicked()
{

    QFileInfo path = returnSelectedPath();

    if (path.absoluteFilePath() == "") {
        QMessageBox msgBox;
        msgBox.setInformativeText(tr("Path cant be root of a directory. Please choose a folder."));
        msgBox.exec();
    }
    else
    {
        QString checkPath = settingsmanager->valueExists(path.absoluteFilePath());
        if (checkPath != "false") {
            QMessageBox msgBox;
            msgBox.setInformativeText(tr("Path already set as ") + checkPath);
            msgBox.exec();
        }
        else {
            saveDirectories(MainWindow::settingsKeyForPaths, path.baseName(), path.absoluteFilePath());

            ui->tableWidget->insertRow(ui->tableWidget->rowCount());

            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(path.absoluteFilePath()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(path.baseName()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(path.lastModified().toUTC().toString(tr("dd.MM.yyyy hh:mm"))));
        }
    }

}

void Window::on_pushButton_addWorkDir_clicked()
{
    QFileInfo fInfo = returnSelectedPath();

    if (fInfo.absoluteFilePath() == "") {
        QMessageBox msgBox;
        msgBox.setInformativeText(tr("Path cant be root of a directory. Please choose a folder."));
        msgBox.exec();
    }
    else
    {
        QString checkPath = settingsmanager->valueExists(fInfo.absoluteFilePath());
        if (checkPath != "false") {
            QMessageBox msgBox;
            msgBox.setInformativeText(tr("Path already set as ") + checkPath);
            msgBox.exec();
        }
        else {

            //saveDirectories(MainWindow::settingsKeyForWorkDirPath, fInfo.baseName(), fInfo.absoluteFilePath());
            saveDirectories(MainWindow::settingsKeyForWorkDirPath, "workdir", fInfo.absoluteFilePath());

            //Setup the default value key for contextmenu tray icon open action on first start
            //once default path is set in settings, new path is set in Window::on_pushButton_setdefaultopenaction_clicked
            if (!settingsmanager->keyExists(MainWindow::settingsKeyGeneralSettings, "defaultopendir")) {
                saveDirectories(MainWindow::settingsKeyGeneralSettings, "defaultopendir", fInfo.absoluteFilePath());
            }

            ui->tableWidget_dir->insertRow(ui->tableWidget_dir->rowCount());

            ui->tableWidget_dir->setItem(ui->tableWidget_dir->rowCount()-1, 0, new QTableWidgetItem(fInfo.absoluteFilePath()));
            ui->tableWidget_dir->setItem(ui->tableWidget_dir->rowCount()-1, 1, new QTableWidgetItem(fInfo.baseName()));
            ui->tableWidget_dir->setItem(ui->tableWidget_dir->rowCount()-1, 2, new QTableWidgetItem(fInfo.lastModified().toUTC().toString(tr("dd.MM.yyyy hh:mm"))));


            //Allow user to only add one working directory
            ui->pushButton_addWorkDir->setEnabled(false);
        }
    }


}

void Window::on_pushButton_AddCloud_clicked()
{
    QFileInfo path = returnSelectedPath();

    if (path.absoluteFilePath() == "") {
        QMessageBox msgBox;
        msgBox.setInformativeText(tr("Path cant be root of a directory. Please choose a folder."));
        msgBox.exec();
    }
    else
    {
        QString checkPath = settingsmanager->valueExists(path.absoluteFilePath());
        if (checkPath != "false") {
            QMessageBox msgBox;
            msgBox.setInformativeText(tr("Path already set as ") + checkPath);
            msgBox.exec();
        }
        else {
            //stored in group workdirpath because for workdir and cloud can only be chooses one dir
            saveDirectories(MainWindow::settingsKeyForCloudDirPath, "clouddir", path.absoluteFilePath());

            ui->tableWidget_cloud->insertRow(ui->tableWidget_cloud->rowCount());

            ui->tableWidget_cloud->setItem(ui->tableWidget_cloud->rowCount()-1, 0, new QTableWidgetItem(path.absoluteFilePath()));
            ui->tableWidget_cloud->setItem(ui->tableWidget_cloud->rowCount()-1, 1, new QTableWidgetItem(path.baseName()));
            ui->tableWidget_cloud->setItem(ui->tableWidget_cloud->rowCount()-1, 2, new QTableWidgetItem(path.lastModified().toUTC().toString(tr("dd.MM.yyyy hh:mm"))));

            //Allow user to only add one working directory
            ui->pushButton_AddCloud->setEnabled(false);
        }
    }
}


void Window::on_pushButton_deleteDir_clicked()
{
    QItemSelectionModel *select = ui->tableWidget->selectionModel();
    QModelIndexList indexList = select->selectedIndexes();

    foreach (QModelIndex index, indexList) {
        int row = index.row();
        QString name = ui->tableWidget->item(row, 1)->text();

        settingsmanager->removeKey(MainWindow::settingsKeyForPaths, name);
        ui->tableWidget->removeRow(row);
    }

    if(ui->tableWidget->rowCount() == 0) {
        Timer::GetInstance().stop();
    }

}

void Window::on_pushButton_deleteDir_2_clicked()
{
    Timer::GetInstance().stop();
    QItemSelectionModel *selectDir = ui->tableWidget_dir->selectionModel();

    //QModelIndexList indexListDir = selectDir->selectedIndexes();

    //if (!indexListDir.isEmpty()) {
        //foreach (QModelIndex index, indexListDir) {
            //int row = index.row();
            QString name = ui->tableWidget_dir->item(0, 1)->text();

            settingsmanager->removeKey(MainWindow::settingsKeyForWorkDirPath, "workdir");
            ui->tableWidget_dir->removeRow(0);
        //}
   // }
            /*
    else {
        QMessageBox msgBox;
        msgBox.setInformativeText(tr("Please select path to delete."));
        msgBox.exec();
    }
    */
    ui->pushButton_addWorkDir->setEnabled(true);
}

void Window::on_pushButton_delete_cloud_clicked()
{
    Timer::GetInstance().stop();
    QItemSelectionModel *select = ui->tableWidget_cloud->selectionModel();
    /*QModelIndexList indexList = select->selectedIndexes();

    foreach (QModelIndex index, indexList) {
        int row = index.row();
        */
        QString name = ui->tableWidget_cloud->item(0, 1)->text();

        settingsmanager->removeKey(MainWindow::settingsKeyForCloudDirPath, "clouddir");
        ui->tableWidget_cloud->removeRow(0);
    //}
    ui->pushButton_AddCloud->setEnabled(true);
}

void Window::on_pushButton_confirm_clicked()
{
    if (settingsmanager->groupExists(MainWindow::settingsKeyForWorkDirPath) &&
                  settingsmanager->groupExists(MainWindow::settingsKeyForCloudDirPath)) {
        //Copy whole dirs on confirming changes
        checkAndCopy();
        //Start timer which check every x Seconds if there are changes in the specified directories
        startAutoSync();
    }
    else {
        QMessageBox msgBox;
        msgBox.setInformativeText(tr("Please specify workdir and clouddir first."));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.exec();
    }


}

void Window::set_copyStatusTip() {
    qDebug() << "Window set_copystatustip: " << "Copy and encryption of files done";
    act3->setStatusTip(tr("Copy and encryption of files done"));
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

    ui->treeView_dirBrowser->setModel(fileBrowserModel);
    ui->treeView_dirBrowser->setColumnWidth(0,300);
}


void Window::initializeTableWidget(QTableWidget *widget) {
    QStringList title;
    title << tr("Path") << tr("Name") << tr("Date Modified");
    widget->setColumnCount(3);
    widget->setHorizontalHeaderLabels(title);
    widget->setColumnWidth(0, 300);
    widget->setColumnWidth(1, 100);
    widget->horizontalHeader()->setStretchLastSection(true);
    widget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    widget->setShowGrid(false);
    widget->setWordWrap(false);
}


void Window::saveDirectories(QString group, QString name, QString path) {
    //Adding name for getting the full path including selected folder
    if (!settingsmanager->keyExists(group, name)) {
       settingsmanager->saveSettings(group, name, path);
    }
    else {
        QMessageBox msgBox;
        msgBox.setInformativeText(tr("Last Entry will be overwritten."));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        switch (msgBox.exec()) {
            case QMessageBox::Ok:
                settingsmanager->removeKey(group, name);
                settingsmanager->saveSettings(group, name, path);
                break;
            case QMessageBox::Cancel:
                // Cancel was clicked
                break;
            default:
                // should never be reached
                break;
          }
    }
}



void Window::populateTableWidget(QString group, QTableWidget *widget) {
   if (!settingsmanager->loadSettings(group).isEmpty()) {
       if (group == MainWindow::settingsKeyForWorkDirPath) {
           //Only allow user to specify one working directory
           ui->pushButton_addWorkDir->setEnabled(false);

       }
       if (group == MainWindow::settingsKeyForCloudDirPath) {
           //Only allow user to specify one working directory
           ui->pushButton_AddCloud->setEnabled(false);

       }
        QStringList keys = settingsmanager->loadSettings(group);
        foreach (QString m_key, keys) {
            QFileInfo path(settingsmanager->returnSetting(group, m_key));
            widget->insertRow(widget->rowCount());
            widget->setItem(widget->rowCount()-1, 0, new QTableWidgetItem(path.absoluteFilePath()));
            widget->setItem(widget->rowCount()-1, 1, new QTableWidgetItem(path.baseName()));
            widget->setItem(widget->rowCount()-1, 2, new QTableWidgetItem(path.lastModified().toUTC().toString(tr("dd.MM.yyyy hh:mm"))));
       }
    }
}

void Window::deleteDirectories(QString name) {
    if (settingsmanager->keyExists(MainWindow::settingsKeyForPaths, name)) {
        settingsmanager->removeKey(MainWindow::settingsKeyForPaths, name);
    }
}

QFileInfo Window::returnSelectedPath() {
    QWidget *currentWidget = QApplication::focusWidget();
    QTreeView *model;
    QFileInfo path;
    if (currentWidget->parentWidget()->objectName() == "ManageWorkSaveDir") {
        model = ui->treeView_dirBrowser;
    }
    else {
        model = ui->treeView_fileBrowser;
    }
    if (fileBrowserModel->fileInfo(model->currentIndex()).baseName().length() != 0){
        path = QFileInfo(fileBrowserModel->fileInfo(model->currentIndex()).absolutePath() + "/" + fileBrowserModel->fileInfo(model->currentIndex()).baseName());
    }
    else {
        return path;
    }
    return path;
}

void Window::copyDirectory(){
    /*
     * this implementation assumes that every directory which should be encrypted are stored to the same workdirectory and cloud
     *
     */

    //get all directories which user has specified to encrypt
    QStringList dirsToEncryp = settingsmanager->loadSettings(MainWindow::settingsKeyForPaths);
    //Load first, and in this case only, key from specified working direcotries
    QString toWork = settingsmanager->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir");
    QString toCloud = settingsmanager->returnSetting(MainWindow::settingsKeyForCloudDirPath, "clouddir");

    foreach (QString nameOfDir, dirsToEncryp) {
        /*
         * Dont copy if folder already exists, which means copy was done before
         */
        QString from = settingsmanager->returnSetting(MainWindow::settingsKeyForPaths, nameOfDir);
        QString toNewWork = filesHandler->createDir(toWork, nameOfDir);
        QString toNewCloud = filesHandler->createDir(toCloud, nameOfDir);

        filesHandler->copy_dir_recursive(from, toNewWork, false);
        filesHandler->copy_dir_recursive(from, toNewCloud, true);
    }
}

void Window::checkAndCopy() {

    QThread *thread = new QThread();

    worker = new Worker();
    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process())) ;
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(thread, SIGNAL(finished()), this, SLOT(set_copyStatusTip()));
    thread->start();

}

void Window::startAutoSync(){
    Timer::GetInstance().stop();
    Timer::GetInstance().start();
}

