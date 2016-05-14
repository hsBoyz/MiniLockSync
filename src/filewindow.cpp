#include "filewindow.h"
#include "ui_filewindow.h"
#include "mainwindow.h"
#include "login.hpp"
#include "window.h"
#include "ui_window.h"
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
    log = new login();
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
        msgBox.setInformativeText(tr("You cannot copy into the root folder."));
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
    msgBox.setText(tr("File/Dir will be deleted."));
    msgBox.setInformativeText(tr("Do you want to delete the File/DirectoryS?"));
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

void FileWindow::on_pushButton_encrypt_clicked()
{
    QFileInfo fileInfo = QFileInfo(selectedDirPath);
    uCrypt::uCryptLib mainSession = log->getMainSession();


    QFileInfo fileInfo2 = QFileInfo(fileInfo.absoluteFilePath() + ".encrypted");

    QString dirCleanedPath = returnDirectoryCleanedPath(currentDirPath);
    QString nameOfEncryptedFolder = returnDirNameFromString(dirCleanedPath);
    QString relativePath = returnRelativPath(dirCleanedPath);

    qDebug() << TAG << "on_pushButton_encrypt_clicked" << dirCleanedPath;
    qDebug() << TAG << "on_pushButton_encrypt_clicked" << nameOfEncryptedFolder;
    qDebug() << TAG << "on_pushButton_encrypt_clicked" << relativePath;
    qDebug() << TAG << "on_pushButton_encrypt_clicked" << fileInfo.absoluteFilePath();
    qDebug() << TAG << "on_pushButton_encrypt_clicked" << setman->returnSetting(MainWindow::settingsKeyForPaths, nameOfEncryptedFolder) + relativePath + QDir::separator() + fileInfo2.completeBaseName();

    //copyDropFiles(fileInfo2.absoluteFilePath(), nameOfEncryptedFolder, relativePath, fileInfo2);
    QString savePath = setman->returnSetting(MainWindow::settingsKeyForPaths, nameOfEncryptedFolder) + relativePath + QDir::separator() + fileInfo2.completeBaseName();

    checkForErrors(mainSession.EncryptFile(fileInfo.fileName().toStdString(), fileInfo.absolutePath().toStdString(), nullptr, 0));
}

void FileWindow::on_pushButton_decrypt_clicked()
{

    QFileInfo fileInfo = QFileInfo(selectedDirPath);
    uCrypt::uCryptLib mainSession = log->getMainSession();
    qDebug() << TAG <<  "on_pushButton_decrypt_clicked: fileName: " << fileInfo.fileName() << " FilePath: " << fileInfo.absolutePath();

    //checkForErrors(mainSession.DecryptFile(fileInfo.fileName().toStdString(), fileInfo.absolutePath().toStdString()));

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

    QString sPath1 = setman->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir");
    currentDirPath = sPath1;

    filemodel->setRootPath(sPath1);

    ui->listView->setModel(filemodel);
    ui->listView->setRootIndex(filemodel->index(sPath1));
}

/*
 * returns relative path
 */
QString FileWindow::returnDirectoryCleanedPath(QString path) {
    QString defaultPath = setman->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir");
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
    QString toWorkDir = setman->returnSetting(MainWindow::settingsKeyForWorkDirPath, setman->getKeyAtPosition(MainWindow::settingsKeyForWorkDirPath, 0))
            + QDir::separator() + folderName + relativePath;

    fileExists(toWorkDir, fileinfo);

    if(fileinfo.isFile()) {
        if(fileinfo.suffix() == "encrypted") {
            //Dateiendung entfernen für mehr Sicherheit?

            if (QFile::copy(from, toCloudDir + QDir::separator() + fileinfo.completeBaseName() + "." + fileinfo.suffix())) {
                QFile::remove(from);
                QFile::remove(toCloudDir + QDir::separator() + fileinfo.completeBaseName());
            }


        }
        else {

            QFile::copy(from, toCloudDir + QDir::separator() + fileinfo.baseName() + "."  + fileinfo.suffix());
            QFile::copy(from, toWorkDir + QDir::separator() + fileinfo.baseName() + "."  + fileinfo.suffix());

        }
    }
    else if (fileinfo.isDir()) {
        //Create folder with name from root folder which should be copied
        fileshandler->createDir(toCloudDir, fileinfo.baseName() + "."  + fileinfo.suffix());
        fileshandler->createDir(toWorkDir, fileinfo.baseName() + "."  + fileinfo.suffix());

        fileshandler->copy_dir_recursive(from, toCloudDir + QDir::separator() + fileinfo.baseName() + "." + fileinfo.suffix(), true);
        fileshandler->copy_dir_recursive(from, toWorkDir + QDir::separator() + fileinfo.baseName() + "."  + fileinfo.suffix(), false);

    }

}

void FileWindow::fileExists(QString path, QFileInfo fileInfo) {
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setInformativeText(tr("File ") + path + QDir::separator() + fileInfo.baseName() + "."  + fileInfo.suffix() + tr(" already exists. Please rename it."));

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

}

void FileWindow::deleteFile(QString folderName, QString relativePath, QFileInfo fileInfo) {

    //Specify paths of working directory and cloud service directory
    QString deleteOriginals = setman->returnSetting(MainWindow::settingsKeyForPaths, folderName) + QDir::separator() + relativePath;
    QString deleteCloudDir = setman->returnSetting(MainWindow::settingsKeyForCloudDirPath, "clouddir") + QDir::separator() + folderName + QDir::separator() + relativePath;
    QString deleteWorkDir = setman->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir") + QDir::separator() + folderName + QDir::separator() + relativePath;

    if (fileInfo.isDir()) {
        //fileshandler->delete_dir_recursive(deleteOriginals);
        fileshandler->delete_dir_recursive(deleteCloudDir);
        fileshandler->delete_dir_recursive(deleteWorkDir);

        /* TODO: Wenn ordner root ordner ist, dann aus einstellungen und tablewidget löschen
        if (relativePath == "") {
            Window *w;
            QList<QTableWidgetItem *> list = w->ui->tableWidget->findItems(folderName, Qt::MatchFixedString);

            if(list.length() == 1) {
                qDebug() << "Remove row" << list.value(0)->row();
                w->ui->tableWidget->item(0, 0)->setBackground(Qt::red);
                w->ui->tableWidget->removeRow(list.value(0)->row());
            }
        }
        */
    }
    else {

        QFile::remove(deleteCloudDir);
        QFile::remove(deleteWorkDir);
        //QFile::remove(deleteOriginals);

    }
}



void FileWindow::checkForErrors(int result)
{
    switch(result)
    {
    case 1: // Encryption Error
        {
            QMessageBox::critical(this, tr("General Encryption Error"),
            tr("Something went wrong with the encryption"));
            break;
        }

    case 2: // Decryption Error
        {
            QMessageBox::critical(this, tr("General Decryption Error"),
            tr("Something went wrong with the decryption"));
            break;
        }

    case 3: // JSON Parsing Error
        {
            QMessageBox::critical(this, tr("General JSON Parsing Error"),
            tr("Library returned with the Error Code for a JSON Parsing Error!"));
            break;
        }

    case 4: // Invalid Header Version
        {
            QMessageBox::critical(this, tr("Invalid Header Version"),
            tr("Library returned with the Error Code for a Invalid Header Version!"));
            break;
        }

    case 5: // Invalid Sender
        {
            QMessageBox::critical(this, tr("Invalid Sender"),
            tr("Library returned with the Error Code for a Invalid Sender!"));
            break;
        }

    case 6: // Invalid Recipient
        {
            QMessageBox::critical(this, tr("Invalid Recipient"),
            tr("Library returned with the Error Code for a Invalid Recipient!"));
            break;
        }

    case 7: // Invalid File Hash
        {
            QMessageBox::critical(this, tr("Invalid File Hash"),
            tr("Library returned with the Error Code for a Invalid File Hash!"));
            break;
        }

    case 0xfe: // General File Read Error
        {
            QMessageBox::critical(this, tr("General File Read Error"),
            tr("Please select a file to encrypt"));
            break;
        }

    case 0xff: // Library not initialized
        {
            QMessageBox::critical(this, tr("Library not initialized"),
            tr("Library was called without beeing initialized correctly!"));
            break;
        }
    }
}
