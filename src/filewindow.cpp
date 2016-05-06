#include "filewindow.h"
#include "ui_filewindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDesktopServices>
#include <QMessageBox>
#include <QMimeData>

FileWindow::FileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    setman = new Settingsmanager();
    fileshandler = new Handlefiles();
    setFileModels();
}

FileWindow::~FileWindow()
{
    delete ui;
}

/*
 *
 *
 *
 * Slot functions
 *
 *
 *
 */

void FileWindow::on_pushButton_back_clicked()
{
    if (!previousDirPath.isEmpty()) {
        ui->listView->setRootIndex(filemodel->index(previousDirPath.last()));
        previousDirPath.removeLast();
    }

    selectedDirPath = "";
}

void FileWindow::on_listView_activated(const QModelIndex &index)
{
    currentDirPath = filemodel->fileInfo(index).absoluteFilePath();
    previousDirPath.append(filemodel->fileInfo(index).absolutePath());
}

void FileWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    if (filemodel->fileInfo(index).isDir()) {
        //Step into folder
        ui->listView->setRootIndex(index);
        //previousDirPath.append(filemodel->fileInfo(index).absolutePath());
    }
    else {
        //Open document with system standard application
        QDesktopServices::openUrl(filemodel->fileInfo(index).absoluteFilePath());
    }
}


void FileWindow::dragEnterEvent(QDragEnterEvent *e)
{
    e->acceptProposedAction();
}

void FileWindow::dragLeaveEvent(QDragLeaveEvent *e)
{
    e->accept();
}

void FileWindow::dragMoveEvent(QDragMoveEvent *e)
{
    e->acceptProposedAction();
}

void FileWindow::dropEvent(QDropEvent *e)
{
    //copy droped files to folder which is shown currently
    QString copyTo = currentDirPath;
    QString dirCleanedPath;
    QString nameOfEncryptedFolder;
    QString relativePath;

    //dont allow to copy a file/dir into working directory root folder
    if (copyTo == setman->returnSetting(MainWindow::settingsKeyGeneralSettings, "defaultopenpath")) {
        QMessageBox msgBox;
        msgBox.setInformativeText("You cannot copy into the root folder.");
        msgBox.exec();
    }
    else {
        dirCleanedPath = returnDirectoryCleanedPath(copyTo);
        nameOfEncryptedFolder = returnDirNameFromString(dirCleanedPath);
        relativePath = returnRelativPath(dirCleanedPath);

        if (e->mimeData()->hasUrls()) {
            foreach (QUrl url, e->mimeData()->urls()) {
                QString localPath = url.toLocalFile();
                QFileInfo fileInfo(localPath);
                copyDropFiles(url.toLocalFile(), nameOfEncryptedFolder, relativePath, fileInfo);
            }
        }
    }
}

void FileWindow::on_listView_clicked(const QModelIndex &index)
{
    selectedDirPath = filemodel->fileInfo(index).absoluteFilePath();
}

void FileWindow::on_pushButton_deleteFile_clicked()
{
    QString dirCleanedPath;
    QString nameOfEncryptedFolder;
    QString relativePath;

    QMessageBox msgBox;
    msgBox.setText("File/Dir will be deleted.");
    msgBox.setInformativeText("Do you want to delete the File/DirectoryS?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    dirCleanedPath = returnDirectoryCleanedPath(selectedDirPath);
    nameOfEncryptedFolder = returnDirNameFromString(dirCleanedPath);
    relativePath = returnRelativPath(dirCleanedPath);

    QFileInfo fileInfo(selectedDirPath);

    if (selectedDirPath != "") {
        int returnValue = msgBox.exec();

        switch (returnValue) {
            case QMessageBox::Ok:
                deleteFile(nameOfEncryptedFolder, relativePath, fileInfo);
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


/*
 *
 *
 *
 * general functions
 *
 *
 *
 */

void FileWindow::setFileModels() {

    previousDirPath.clear();

    filemodel = new QFileSystemModel(this);

    /**
     * @brief NO dynamic implementation yet. Group of sPath1 is hardcoded
     */

    QString sPath1 = setman->returnSetting(MainWindow::settingsKeyGeneralSettings, "defaultopenpath");
    currentDirPath = sPath1;

    filemodel->setRootPath(sPath1);

    ui->listView->setModel(filemodel);
    ui->listView->setRootIndex(filemodel->index(sPath1));
}

/*
 * returns relative path
 */
QString FileWindow::returnDirectoryCleanedPath(QString path) {
    QString defaultPath = setman->returnSetting(MainWindow::settingsKeyGeneralSettings, "defaultopenpath");
    int removeTo = defaultPath.length() + 1;    //+1 to also eliminate the last seperator

    return path.remove(0,removeTo);
}

QString FileWindow::returnRelativPath(QString path) {
    QString nativeSeperatorsPath = QDir::toNativeSeparators(path);
    QStringList parts = nativeSeperatorsPath.split(QDir::separator());
    QString returnString = "";
    for (int i = 1; i < parts.length(); i++) {
        returnString += QDir::separator() + parts[i];
    }
    return returnString;
}

QString FileWindow::returnDirNameFromString(QString path) {
    QString nativeSeperatorsPath = QDir::toNativeSeparators(path);
    QStringList parts = nativeSeperatorsPath.split(QDir::separator());
    return parts[0];
}

void FileWindow::copyDropFiles(QString from, QString folderName, QString relativePath, QFileInfo fileinfo) {
    //Specify paths of working directory, saftycopy directory and cloud service directory
    QString toCloudDir = setman->returnSetting(MainWindow::settingsKeyForPaths, folderName) + relativePath;
    QString toWorkDir = setman->returnSetting(MainWindow::settingsKeyForSaveDirPath, setman->getKeyAtPosition(MainWindow::settingsKeyForSaveDirPath, 0))
            + QDir::separator() + folderName + relativePath;
    QString toSaveDir = setman->returnSetting(MainWindow::settingsKeyForWorkDirPath, setman->getKeyAtPosition(MainWindow::settingsKeyForWorkDirPath, 0))
            + QDir::separator() + folderName + relativePath;

    fileExists(toWorkDir, fileinfo);

    if(fileinfo.isFile()) {
        QFile::copy(from, toCloudDir + QDir::separator() + fileinfo.baseName() + "."  + fileinfo.suffix());
        QFile::copy(from, toWorkDir + QDir::separator() + fileinfo.baseName() + "."  + fileinfo.suffix());
        QFile::copy(from, toSaveDir + QDir::separator() + fileinfo.baseName() + "."  + fileinfo.suffix());
    }
    else if (fileinfo.isDir()) {
        //Create folder with name from root folder which should be copied
        fileshandler->createDir(toCloudDir, fileinfo.baseName() + "."  + fileinfo.suffix());
        fileshandler->createDir(toSaveDir, fileinfo.baseName() + "."  + fileinfo.suffix());
        fileshandler->createDir(toWorkDir, fileinfo.baseName() + "."  + fileinfo.suffix());

        fileshandler->copy_dir_recursive(from, toCloudDir + QDir::separator() + fileinfo.baseName() + "." + fileinfo.suffix());
        fileshandler->copy_dir_recursive(from, toWorkDir + QDir::separator() + fileinfo.baseName() + "."  + fileinfo.suffix());
        fileshandler->copy_dir_recursive(from, toSaveDir + QDir::separator() + fileinfo.baseName() + "."  + fileinfo.suffix());
    }

}

void FileWindow::fileExists(QString path, QFileInfo fileInfo) {
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setInformativeText("File " + path + QDir::separator() + fileInfo.baseName() + "."  + fileInfo.suffix() + " already exists. Please rename it.");
    msgBox.exec();
    /*
    if (QFile::exists(path + QDir::separator() + fileInfo.baseName() + "."  + fileInfo.suffix())) {
        switch (msgBox.exec()) {
            case QMessageBox::Ok:
                QFile::remove(path + QDir::separator() + fileInfo.baseName() + "."  + fileInfo.suffix());
                break;
            case QMessageBox::Cancel:
                // Cancel was clicked
                break;
            default:
                // should never be reached
                break;
          }
    }
    */
}

void FileWindow::deleteFile(QString folderName, QString relativePath, QFileInfo fileInfo) {

    //Specify paths of working directory, saftycopy directory and cloud service directory
    QString deleteCloudDir = setman->returnSetting(MainWindow::settingsKeyForPaths, folderName) + QDir::separator() + relativePath;
    QString deleteWorkDir = setman->returnSetting(MainWindow::settingsKeyForSaveDirPath, setman->getKeyAtPosition(MainWindow::settingsKeyForSaveDirPath, 0))
            + QDir::separator() + folderName + QDir::separator() + relativePath;
    QString deleteSaveDir = setman->returnSetting(MainWindow::settingsKeyForWorkDirPath, setman->getKeyAtPosition(MainWindow::settingsKeyForWorkDirPath, 0))
            + QDir::separator() + folderName + QDir::separator() + relativePath;

    if (fileInfo.isDir()) {
        fileshandler->delete_dir_recursive(deleteCloudDir);
        fileshandler->delete_dir_recursive(deleteWorkDir);
        fileshandler->delete_dir_recursive(deleteSaveDir);
    }
    else {
        QFile::remove(deleteCloudDir);
        QFile::remove(deleteWorkDir);
        QFile::remove(deleteSaveDir);
    }
}
