#include "filewindow.h"
#include "ui_filewindow.h"
#include "mainwindow.h"
#include "handlefiles.h"

#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDesktopServices>
#include <QMessageBox>


FileWindow::FileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);

    setman = new Settingsmanager();
    filesHandler = new HandleFiles();

    createCopyAndWorkDir();
    copyDirectory();
    setFileModels();



}

FileWindow::~FileWindow()
{
    delete ui;
}

void FileWindow::setFileModels() {
    previousDirPath.clear();

    filemodel_saftycopy = new QFileSystemModel(this);
    QString sPath1 = setman->returnSetting(MainWindow::settingsKeyForSaveDir, "mainfolder");
    filemodel_saftycopy->setRootPath(sPath1);

    ui->listView_saftyCopy->setModel(filemodel_saftycopy);
    ui->listView_saftyCopy->setRootIndex(filemodel_saftycopy->index(sPath1));

    /*
     *
     *
     * NO dynamic implementation yet. sPath2 getKeyAtPosition
     *
     *
     *
    */
    filemodel_2 = new QFileSystemModel(this);
    QString sPath2 = setman->returnSetting(MainWindow::settingsKeyForPaths, setman->getKeyAtPosition(MainWindow::settingsKeyForPaths, 0));
    filemodel_2->setRootPath(sPath2);

    ui->listView_2->setModel(filemodel_2);
    ui->listView_2->setRootIndex(filemodel_2->index(sPath2));
    currentDirPath = sPath2;

    ui->label->setText(setman->getKeyAtPosition(MainWindow::settingsKeyForPaths, 0));

}

void FileWindow::dragEnterEvent(QDragEnterEvent *e)
{
    e->acceptProposedAction();
}

void FileWindow::dragLeaveEvent(QDragEnterEvent *e)
{
    e->acceptProposedAction();
}

void FileWindow::dragMoveEvent(QDragEnterEvent *e)
{
    e->acceptProposedAction();
}

void FileWindow::dropEvent(QDropEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        foreach (QUrl url, e->mimeData()->urls()) {
            qDebug() << TAG + " dropEvent, File copied? " << QFile::copy(url.toLocalFile(), (currentDirPath + "/" + url.fileName()));
        }
    }
}

void FileWindow::on_pushButton_clicked()
{
    //save
    setman->saveSettings("Test", "key", "value");
}

void FileWindow::on_pushButton_2_clicked()
{
    //load
    setman->loadSettings("Test");
}

void FileWindow::on_pushButton_3_clicked()
{
    setman->removeAllKeys();
}

void FileWindow::on_pushButton_4_clicked()
{
    setman->printGroups();
}

void FileWindow::on_listView_2_doubleClicked(const QModelIndex &index)
{
    if (filemodel_2->fileInfo(index).isDir()) {
        //Step into folder
        ui->listView_2->setRootIndex(index);
    }
    else {
        //Open document with system standard application
        QDesktopServices::openUrl(filemodel_2->fileInfo(index).absoluteFilePath());
    }

}


void FileWindow::on_listView_2_activated(const QModelIndex &index)
{
    currentDirPath = filemodel_2->fileInfo(index).absoluteFilePath();
    previousDirPath.append(filemodel_2->fileInfo(index).absolutePath());

}

void FileWindow::on_listView_saftyCopy_doubleClicked(const QModelIndex &index)
{
    if (filemodel_saftycopy->fileInfo(index).isDir()) {
        //Step into folder
        ui->listView_saftyCopy->setRootIndex(index);
    }
    else {
        //Open document with system standard application
        QDesktopServices::openUrl(filemodel_saftycopy->fileInfo(index).absoluteFilePath());
    }
}

void FileWindow::on_listView_saftyCopy_activated(const QModelIndex &index)

{
    currentDirPathWorkDir = filemodel_saftycopy->fileInfo(index).absoluteFilePath();
    previousDirPathWorkDir.append(filemodel_saftycopy->fileInfo(index).absolutePath());
}

void FileWindow::on_pushButton_5_clicked()
{
    if (!previousDirPath.isEmpty()) {
        ui->listView_2->setRootIndex(filemodel_2->index(previousDirPath.last()));
        previousDirPath.removeLast();
    }
    selectedDirPath = "";

}

void FileWindow::on_pushButton_backSaftyCopy_clicked()
{
    if (!previousDirPathWorkDir.isEmpty()) {
        ui->listView_saftyCopy->setRootIndex(filemodel_saftycopy->index(previousDirPathWorkDir.last()));
        previousDirPathWorkDir.removeLast();
    }
    selectedDirPathWorkDir = "";
}

void FileWindow::on_pushButton_6_clicked()
{
    if (ui->listView_2->viewMode() == QListView::IconMode) {
        ui->listView_2->setViewMode(QListView::ListMode);
    }
    else {
        ui->listView_2->setViewMode(QListView::IconMode);
    }

}

void FileWindow::on_removeFile_clicked()
{
    qDebug() << TAG << " removeFile: selectedDirPath: " << selectedDirPath;

    QMessageBox msgBox;
    msgBox.setText("File will be deleted.");
    msgBox.setInformativeText("Do you want to delete the File?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    if (selectedDirPath != "") {
        int returnValue = msgBox.exec();

        switch (returnValue) {
            case QMessageBox::Ok:
                QFile::remove(selectedDirPath);
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

void FileWindow::on_listView_2_clicked(const QModelIndex &index)
{
    selectedDirPath = filemodel_2->fileInfo(index).absoluteFilePath();
}

void FileWindow::copyDirectory(){

    QString from = setman->returnSetting(MainWindow::settingsKeyForPaths, setman->getKeyAtPosition(MainWindow::settingsKeyForPaths, 0));
    QString to = setman->returnSetting(MainWindow::settingsKeyForSaveDir, "workplace");
    qDebug() << TAG << "copyDirectory from: " << from;
    qDebug() << TAG << "copyDirectory to: " << to;
    filesHandler->copy_dir_recursive(from, to);

    to = setman->returnSetting(MainWindow::settingsKeyForSaveDir, "safetycopy");
    filesHandler->copy_dir_recursive(from, to);



}

void FileWindow::createCopyAndWorkDir() {
    QStringList keys = setman->loadSettings(MainWindow::settingsKeyForSaveDir);
    QString setting = setman->returnSetting(MainWindow::settingsKeyForSaveDir, keys[0]);
    QDir dir = QDir::root();
    if (!QDir(setting + "/MiniLockSync").exists()) {
        qDebug() << TAG << "createCopyAndWorkDir: MiniLockSync Ordner erstellt? " <<
        dir.mkpath(setting + "/MiniLockSync");
        setman->saveSettings(MainWindow::settingsKeyForSaveDir, "mainfolder", setting + "/MiniLockSync");
        setting += "/MiniLockSync";

        if (!QDir(setting + "/Workplace").exists()) {
            qDebug() << TAG << "createCopyAndWorkDir: Workplace Ordner erstellt? " <<
            dir.mkpath(setting + "/Workplace");
            setman->saveSettings(MainWindow::settingsKeyForSaveDir, "workplace", setting + "/Workplace");
        }

        if (!QDir(setting + "/Safetycopy").exists()) {
            qDebug() << TAG << "createCopyAndWorkDir: Safetycopy Ordner erstellt? " <<
            dir.mkpath(setting + "/Safetycopy");
            setman->saveSettings(MainWindow::settingsKeyForSaveDir, "safetycopy", setting + "/Safetycopy");
        }
    }
    else if (QDir(setting + "/MiniLockSync").exists()){

        setting += "/MiniLockSync";

        if (!QDir(setting + "/Workplace").exists()) {
            //qDebug() << TAG << "createCopyAndWorkDir else: Workplace Ordner erstellt? " <<
            dir.mkpath(setting + "/Workplace");
            setman->saveSettings(MainWindow::settingsKeyForSaveDir, "workplace", setting + "/Workplace");
        }

        if (!QDir(setting + "/Safetycopy").exists()) {
            //qDebug() << TAG << "createCopyAndWorkDir else: Safetycopy Ordner erstellt? " <<
            dir.mkpath(setting + "/Safetycopy");
            setman->saveSettings(MainWindow::settingsKeyForSaveDir, "safetycopy", setting + "/Safetycopy");

        }

        if (!setman->keyExists(MainWindow::settingsKeyForSaveDir, "mainfolder")) {
            setman->saveSettings(MainWindow::settingsKeyForSaveDir, "mainfolder", setting + "/MiniLockSync");
        }
        if (!setman->keyExists(MainWindow::settingsKeyForSaveDir, "workplace")) {
            setman->saveSettings(MainWindow::settingsKeyForSaveDir, "workplace", setting + "/Workplace");
        }
        if (!setman->keyExists(MainWindow::settingsKeyForSaveDir, "safetycopy")) {
            setman->saveSettings(MainWindow::settingsKeyForSaveDir, "safetycopy", setting + "/Safetycopy");
        }
    }
}




