#include "window.h"
#include "ui_window.h"
#include <QDebug>
#include <QMessageBox>

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
                    QIcon(QString("%1%2").arg(QCoreApplication::applicationDirPath()).arg("/images/cancel.png"))   ,
                    tr("Quit"),
           qApp, SLOT(quit()),
           QKeySequence(tr("Ctrl+Q", "File|Quit")) );
        act3->setStatusTip(tr("Quit Program"));
        QMenu *workMenu = new QMenu(
           tr("&Edit"), this);
        menuBar()->addMenu(workMenu);
//--------------------------------------------------------

    settingsmanager = new Settingsmanager();

    //Verbinde Ereignis mit Methode

    connect (ui->pushHome, SIGNAL(on_pushHome_clicked()),this, SLOT(setCurrentIndex(int)));
    connect (ui->pushCloudService, SIGNAL(on_pushCloudService_clicked()), SLOT(setCurrentIndex(int)));
    connect (ui->pushManageCloud, SIGNAL(on_pushManageCloud_clicked()), SLOT(setCurrentIndex(int)));
    connect (ui->pushManageSaveDir, SIGNAL(on_pushManageSaveDir_clicked()), SLOT(setCurrentIndex(int)));
    connect (ui->pushCPULimitation, SIGNAL(on_pushCPULimitation_clicked()), SLOT(setCurrentIndex(int)));
    connect (ui->pushChangePassword, SIGNAL(on_pushChangePassword_clicked()), SLOT(setCurrentIndex(int)));



    initializeFileBrowser();
    initializeTableWidget(ui->tableWidget);
    initializeTableWidget(ui->tableWidget_dir);
    initializeTableWidget(ui->tableWidget_save);
    populateTableWidget(MainWindow::settingsKeyForPaths, ui->tableWidget);
    populateTableWidget(MainWindow::settingsKeyForWorkDirPath, ui->tableWidget_dir);
    populateTableWidget(MainWindow::settingsKeyForSaveDirPath, ui->tableWidget_save);
}

Window::~Window()
{
    delete ui;
}
// Kontextmenü verwenden contextMenuEvent
// ist eine virtuelle Methode
void Window::contextMenuEvent(
    QContextMenuEvent *event) {
   QMenu *menu = new QMenu(this);
   //menu->addAction(act1);
   //menu->addAction(act2);
   menu->addAction(act3);
   menu->exec(event->globalPos());
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

void Window::on_pushHome_clicked(int index)
{
    ui->stackedWidget->setCurrentIndex(1);
}
void Window::on_pushCloudService_clicked(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void Window::on_pushManageCloud_clicked(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void Window::on_pushManageSaveDir_clicked(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void Window::on_pushCPULimitation_clicked(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void Window::on_pushChangePassword_clicked(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void Window::on_pushButton_addDir_clicked()
{
    /*
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

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).absolutePath()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(fileBrowserModel->fileInfo(ui->treeView_fileBrowser->currentIndex()).baseName()));
    */

    QList<QString> path = returnSelectedPath();

    if (path.value(0) == "error") {
        QMessageBox msgBox;
        msgBox.setInformativeText("Path cant be root of a directory. Please choose a folder.");
        msgBox.exec();
    }
    else {
        saveDirectories(MainWindow::settingsKeyForPaths, path.value(1), path.value(0));

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(path.value(0)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(path.value(1)));
    }
}

void Window::on_pushButton_addWorkDir_clicked()
{
    QList<QString> path = returnSelectedPath();

    if (path.value(0) == "error") {
        QMessageBox msgBox;
        msgBox.setInformativeText("Path cant be root of a directory. Please choose a folder.");
        msgBox.exec();
    }
    else {
        saveDirectories(MainWindow::settingsKeyForWorkDirPath, path.value(1), path.value(0));

        ui->tableWidget_dir->insertRow(ui->tableWidget->rowCount());

        ui->tableWidget_dir->setItem(ui->tableWidget_dir->rowCount()-1, 0, new QTableWidgetItem(path.value(0)));
        ui->tableWidget_dir->setItem(ui->tableWidget_dir->rowCount()-1, 1, new QTableWidgetItem(path.value(1)));
    }
}

void Window::on_pushButton_addSaveDir_clicked()
{
    QList<QString> path = returnSelectedPath();

    if (path.value(0) == "error") {
        QMessageBox msgBox;
        msgBox.setInformativeText("Path cant be root of a directory. Please choose a folder.");
        msgBox.exec();
    }
    else {
        saveDirectories(MainWindow::settingsKeyForSaveDirPath, path.value(1), path.value(0));

        ui->tableWidget_save->insertRow(ui->tableWidget->rowCount());

        ui->tableWidget_save->setItem(ui->tableWidget_save->rowCount()-1, 0, new QTableWidgetItem(path.value(0)));
        ui->tableWidget_save->setItem(ui->tableWidget_save->rowCount()-1, 1, new QTableWidgetItem(path.value(1)));
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

}

void Window::on_pushButton_deleteDir_2_clicked()
{
    QItemSelectionModel *selectDir = ui->tableWidget_dir->selectionModel();
    QItemSelectionModel *selectSave = ui->tableWidget_save->selectionModel();

    QModelIndexList indexListDir = selectDir->selectedIndexes();
    QModelIndexList indexListSave = selectSave->selectedIndexes();

    if (!indexListDir.isEmpty()) {
        foreach (QModelIndex index, indexListDir) {
            int row = index.row();
            QString name = ui->tableWidget_dir->item(row, 1)->text();

            settingsmanager->removeKey(MainWindow::settingsKeyForWorkDirPath, name);
            ui->tableWidget_dir->removeRow(row);
        }
    }
    else if (!indexListSave.isEmpty()) {
        foreach (QModelIndex index, indexListSave) {
            int row = index.row();
            QString name = ui->tableWidget_save->item(row, 1)->text();

            settingsmanager->removeKey(MainWindow::settingsKeyForSaveDirPath, name);
            ui->tableWidget_save->removeRow(row);
        }
    }
    else {
        QMessageBox msgBox;
        msgBox.setInformativeText("Please select path to delete.");
        msgBox.exec();
    }
}

void Window::on_pushButton_confirm_clicked()
{

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
    title << "Pfad" << "Name";
    widget->setColumnCount(2);
    widget->setHorizontalHeaderLabels(title);
    widget->setColumnWidth(0, 300);
    widget->horizontalHeader()->setStretchLastSection(true);
}


void Window::saveDirectories(QString group, QString name, QString path) {
    //Adding name for getting the full path including selected folder
    if (!settingsmanager->keyExists(group, name)) {
       settingsmanager->saveSettings(group, name, path);
    }
}



void Window::populateTableWidget(QString group, QTableWidget *widget) {
    if (!settingsmanager->loadSettings(group).isEmpty()) {
        QStringList keys = settingsmanager->loadSettings(group);
        foreach (QString key, keys) {
            QDir dir = (settingsmanager->returnSetting(group, key));
            widget->insertRow(widget->rowCount());
            widget->setItem(widget->rowCount()-1, 0, new QTableWidgetItem(dir.absolutePath()));
            widget->setItem(widget->rowCount()-1, 1, new QTableWidgetItem(dir.dirName()));
        }
    }
}

void Window::deleteDirectories(QString name) {
    if (settingsmanager->keyExists(MainWindow::settingsKeyForPaths, name)) {
        settingsmanager->removeKey(MainWindow::settingsKeyForPaths, name);
    }
}

QList<QString> Window::returnSelectedPath() {
    QWidget *currentWidget = QApplication::focusWidget();
    QTreeView *model;
    QList<QString> path;
    path.clear();
    if (currentWidget->parentWidget()->objectName() == "ManageWorkSaveDir") {
        model = ui->treeView_dirBrowser;
    }
    else {
        model = ui->treeView_fileBrowser;
    }
    if (fileBrowserModel->fileInfo(model->currentIndex()).baseName().length() != 0){
        path.append(fileBrowserModel->fileInfo(model->currentIndex()).absolutePath() + "/" + fileBrowserModel->fileInfo(model->currentIndex()).baseName());
        path.append(fileBrowserModel->fileInfo(model->currentIndex()).baseName());
    }
    else {
        /*
        path.append(fileBrowserModel->fileInfo(model->currentIndex()).absolutePath());
        qDebug() << fileBrowserModel->fileInfo(model->currentIndex()).baseName();
        path.append("noName");
        */
        path.append("error");
    }
    return path;
}




