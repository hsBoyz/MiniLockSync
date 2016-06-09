#include "window.h"
#include "ui_window.h"
#include "filewindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QSignalMapper>
#include <QPalette>
#include <QDesktopServices>

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

//----------------------------------------------------------
    // Das komplette Menü zum Hauptprogramm
        QMenu *fileMenu = new QMenu(tr("&File"), this);
        menuBar()->addMenu(fileMenu);



        act1 = fileMenu->addAction(
                    QIcon(":/icons/images/cancel.png")   ,
                    tr("Quit"),
                    qApp, SLOT(quit()),
                    QKeySequence(tr("Ctrl+Q", "File|Quit")) );
        act1->setStatusTip(tr("Quit Program"));



        QMenu *questionMark = new QMenu(tr("&?"), this);
        menuBar()->addMenu(questionMark);

        act2 = questionMark->addAction(
                    QIcon(":icons/images/book4.png"),

                    tr("Instructions"));

        act2->setStatusTip((tr("Instructions")));

        act3 = questionMark->addAction(
                    QIcon(":icons/images/icon_rund.png"),

                    tr("About us"));

        act3->setStatusTip((tr("About us")));







//--------------------------------------------------------

    settingsmanager = new Settingsmanager();
    filesHandler = new Handlefiles();

    //Verbinde Ereignis mit Methode
    connect (ui->pushHome, SIGNAL(clicked(bool)), this, SLOT(on_pushHome_clicked()));
    connect (ui->pushCloudService, SIGNAL(clicked(bool)), this, SLOT(on_pushCloudService_clicked()));
    connect (ui->pushManageCloud, SIGNAL(clicked(bool)), this, SLOT(on_pushManageCloud_clicked()));
    connect (ui->pushManageSaveDir, SIGNAL(clicked(bool)), this, SLOT(on_pushManageSaveDir_clicked()));

    connect(act2, SIGNAL(triggered()), this, SLOT(menubar_instructions()));
    connect(act3, SIGNAL(triggered()), this, SLOT(menubar_aboutus()));





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

    checkWidget = new QLabel;
    checkWidget->setPixmap(QPixmap(":/icons/images/check_icon.png").scaledToHeight(30));

    syncWidget = new QLabel;
    syncWidget->setPixmap(QPixmap(":/icons/images/sync_icon2.png").scaledToHeight(30));

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

void Window::menubar_instructions(){



    //QDesktopServices::openUrl(QUrl::fromLocalFile(":/docs/MiniLockSync - Instructions.pdf"));
    QDesktopServices::openUrl(QUrl("https://github.com/hsBoyz/MiniLockSync/blob/GUI_Luca/docs/MiniLockSync%20-%20Instructions.pdf"));

}



void Window::menubar_aboutus(){

    QMessageBox about;
    about.setWindowIcon(QPixmap(":icons/images/icon_rund.png"));
    about.setText(tr("MiniLockSync Vers.: 1.0 \n\nMinilock Sync is a Study-related Project of the course SWB. \n\nParticipating developers: \nEugen Rudel, Luca Hanf, Manuel Tutsch, Daniel Seitz, Fabian Högl"));
    about.exec();
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

void Window::on_pushButton_addDir_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(
                this,
                tr("Add folders to encrypt"),
                "C://",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                );
    QFileInfo path = folderPath;

    if (folderPath == "") {
        //Do nothing when user cancel dialog
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
    /*
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
    */

}

void Window::on_pushButton_addWorkDir_clicked()
{

    QString workDirPath = QFileDialog::getExistingDirectory(
                this,
                tr("Add working directory"),
                "C://",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                );

    QString checkPath = settingsmanager->valueExists(workDirPath);
    QFileInfo fInfo = workDirPath;

    if (workDirPath == "") {
        //Do nothing when user cancel dialog
    }

    else if (checkPath != "false") {
        QMessageBox msgBox;
        msgBox.setInformativeText(tr("Path already set as ") + checkPath);
        msgBox.exec();
    }
    else {

        //saveDirectories(MainWindow::settingsKeyForWorkDirPath, fInfo.baseName(), fInfo.absoluteFilePath());
        saveDirectories(MainWindow::settingsKeyForWorkDirPath, "workdir", workDirPath);

        ui->tableWidget_dir->insertRow(ui->tableWidget_dir->rowCount());

        ui->tableWidget_dir->setItem(ui->tableWidget_dir->rowCount()-1, 0, new QTableWidgetItem(fInfo.absoluteFilePath()));
        ui->tableWidget_dir->setItem(ui->tableWidget_dir->rowCount()-1, 1, new QTableWidgetItem(fInfo.baseName()));
        ui->tableWidget_dir->setItem(ui->tableWidget_dir->rowCount()-1, 2, new QTableWidgetItem(fInfo.lastModified().toUTC().toString(tr("dd.MM.yyyy hh:mm"))));


        //Allow user to only add one working directory
        ui->pushButton_addWorkDir->setEnabled(false);
    }

}
    /*
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
    */

//}

void Window::on_pushButton_AddCloud_clicked()
{
    QString cloudDirPath = QFileDialog::getExistingDirectory(
                this,
                tr("Add cloud"),
                "C://",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                );

    QString checkPath = settingsmanager->valueExists(cloudDirPath);
    QFileInfo fInfo = cloudDirPath;

    if (cloudDirPath == "") {
        //Do nothing when user cancel dialog
    }

    else if (checkPath != "false") {
        QMessageBox msgBox;
        msgBox.setInformativeText(tr("Path already set as ") + checkPath);
        msgBox.exec();
    }
    else {

        //saveDirectories(MainWindow::settingsKeyForWorkDirPath, fInfo.baseName(), fInfo.absoluteFilePath());
        saveDirectories(MainWindow::settingsKeyForCloudDirPath, "clouddir", cloudDirPath);

        ui->tableWidget_cloud->insertRow(ui->tableWidget_cloud->rowCount());

        ui->tableWidget_cloud->setItem(ui->tableWidget_cloud->rowCount()-1, 0, new QTableWidgetItem(fInfo.absoluteFilePath()));
        ui->tableWidget_cloud->setItem(ui->tableWidget_cloud->rowCount()-1, 1, new QTableWidgetItem(fInfo.baseName()));
        ui->tableWidget_cloud->setItem(ui->tableWidget_cloud->rowCount()-1, 2, new QTableWidgetItem(fInfo.lastModified().toUTC().toString(tr("dd.MM.yyyy hh:mm"))));


        //Allow user to only add one working directory
        ui->pushButton_AddCloud->setEnabled(false);
    }
    /*
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
    */
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
    //QItemSelectionModel *selectDir = ui->tableWidget_dir->selectionModel();

    //QModelIndexList indexListDir = selectDir->selectedIndexes();

    //if (!indexListDir.isEmpty()) {
        //foreach (QModelIndex index, indexListDir) {
            //int row = index.row();
    if (ui->tableWidget_dir->rowCount() != 0) {
            QString name = ui->tableWidget_dir->item(0, 1)->text();

            settingsmanager->removeKey(MainWindow::settingsKeyForWorkDirPath, "workdir");
            ui->tableWidget_dir->removeRow(0);

            ui->pushButton_addWorkDir->setEnabled(true);
    }
        //}
   // }
            /*
    else {
        QMessageBox msgBox;
        msgBox.setInformativeText(tr("Please select path to delete."));
        msgBox.exec();
    }
    */

}

void Window::on_pushButton_delete_cloud_clicked()
{
    Timer::GetInstance().stop();
    //QItemSelectionModel *select = ui->tableWidget_cloud->selectionModel();
    /*QModelIndexList indexList = select->selectedIndexes();

    foreach (QModelIndex index, indexList) {
        int row = index.row();
        */
    if (ui->tableWidget_cloud->rowCount() != 0) {
        QString name = ui->tableWidget_cloud->item(0, 1)->text();

        settingsmanager->removeKey(MainWindow::settingsKeyForCloudDirPath, "clouddir");
        ui->tableWidget_cloud->removeRow(0);

        ui->pushButton_AddCloud->setEnabled(true);
    }
    //}

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


    /*
    ui->treeView_fileBrowser->setModel(fileBrowserModel);
    ui->treeView_fileBrowser->setColumnWidth(0,300);

    ui->treeView_dirBrowser->setModel(fileBrowserModel);
    ui->treeView_dirBrowser->setColumnWidth(0,300);
    */
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
    widget->verticalHeader()->setVisible(false);

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
    /*QWidget *currentWidget = QApplication::focusWidget();
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
    return path;*/
    return "";
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
    QLabel *test = new QLabel;
    test->setPixmap(QPixmap(":/icons/images/sync_icon2.png"));

    worker = new Worker();
    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()),this, SLOT(set_StatusBar_started()));
    connect(thread, SIGNAL(started()), worker, SLOT(processCopyAddedFolders())) ;
    connect(worker, SIGNAL(finished()),this, SLOT(set_StatusBar_finished()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), this, SLOT(showErrorMessage()));

    thread->start();

}
void Window::set_StatusBar_finished(){

    qDebug() << "Window set_StatusBar_finished: sync done";
        ui->statusBar->removeWidget(syncWidget);
        ui->statusBar->addPermanentWidget(checkWidget, 0);

        while (ui->tableWidget->rowCount() > 0) {
            ui->tableWidget->removeRow(0);
        }

        settingsmanager->removeKey(MainWindow::settingsKeyForPaths, "");
        checkWidget->show();
}

void Window::set_StatusBar_started(){

    qDebug() << "Window set_StatusBar_started: start sync";
    ui->statusBar->removeWidget(checkWidget);
    ui->statusBar->addPermanentWidget(syncWidget, 0);
    syncWidget->show();

}

void Window::startAutoSync(){
    Timer::GetInstance().stop();
    Timer::GetInstance().start();
}

void Window::showErrorMessage() {
    if (Worker::errorCounter > 0) {
        QString files;
        foreach (QString string, Worker::errorFilesList) {
            files += string + "\n";
        }

        QString str = QString::number(Worker::errorCounter) + tr(" files couldn't be encrypted. Please check your choosen Cloud!");

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle(tr("WARNING"));
        msgBox.setText(str);
        msgBox.setDetailedText(tr("Files which were not encrypted: \n\n") + files);
        msgBox.exec();
    }
}
