#include "filewindow.h"
#include "ui_filewindow.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "login.hpp"
#include "window.h"
#include "ui_window.h"
#include <QDebug>
#include <QDesktopServices>
#include <QMessageBox>
#include <QMimeData>
#include <QSignalMapper>

QString FileWindow::currentDirPath = "";

FileWindow::FileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    setman = new Settingsmanager();
    fileshandler = new Handlefiles();
    worker = new Worker();
    watcher = new QFileSystemWatcher();

    connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(handleModifiedFile(QString)));
    setFileModels();

    checkWidget = new QLabel;
    checkWidget->setPixmap(QPixmap(":/icons/images/check_icon.png").scaledToHeight(30));

    syncWidget = new QLabel;
    syncWidget->setPixmap(QPixmap(":/icons/images/sync_icon2.png").scaledToHeight(30));
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
        currentDirPath = previousDirPath.last();
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
    selectedDirPath = "";

    if (filemodel->fileInfo(index).isDir()) {
        //Step into folder
        ui->listView->setRootIndex(index);
        //previousDirPath.append(filemodel->fileInfo(index).absolutePath());
    }
    else {
        //Open document with system standard application
        watcher->addPath(filemodel->fileInfo(index).absoluteFilePath());
        QDesktopServices::openUrl(QUrl::fromLocalFile(filemodel->fileInfo(index).absoluteFilePath()));

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
    if (copyTo == setman->returnSetting(MainWindow::settingsKeyForWorkDirPath, "workdir")) {
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
    QString selectedPath = filemodel->filePath(ui->listView->selectionModel()->selectedIndexes().value(0));

    QString dirCleanedPath;
    QString nameOfEncryptedFolder;
    QString relativePath;

    if (selectedPath == "") {
        QMessageBox msgBox;
        msgBox.setInformativeText(tr("Please select file or directory to delete"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

    QFileInfo fileInfo(selectedPath);


    QMessageBox msgBox;
    msgBox.setText(tr("File/Dir will be deleted."));
    msgBox.setInformativeText(tr("Do you want to delete the following file? ") + fileInfo.baseName().toStdString().c_str() + "." + fileInfo.suffix());
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    dirCleanedPath = returnDirectoryCleanedPath(selectedPath);
    nameOfEncryptedFolder = returnDirNameFromString(dirCleanedPath);
    relativePath = returnRelativPath(dirCleanedPath);

    if (selectedPath != "") {
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
   /* QFileInfo fileInfo = QFileInfo(selectedDirPath);
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

<<<<<<< HEAD
    checkForErrors(mainSession.EncryptFile(fileInfo.fileName().toStdString(), fileInfo.absolutePath().toStdString(), nullptr, 0));
=======
    */

    QString qSzFileName = QString(selectedDirPath);
        uCrypt::uCryptLib mainSession = login::GetInstance().getMainSession();

        int numberOfRecipients = login::GetInstance().ui.comboBox->count();
        std::string *recipients = new std::string[numberOfRecipients];

        recipients[0] = login::GetInstance().ui.comboBox->itemText(0).toStdString();

        checkForErrors(mainSession.EncryptFile(QFileInfo(qSzFileName).fileName().toStdString(), QFileInfo(qSzFileName).absolutePath().toStdString(),recipients,numberOfRecipients));

        //QString fileInfo2 = QString(fileInfo.absoluteFilePath() + ".encrypted");

        QString dirCleanedPath = returnDirectoryCleanedPath(currentDirPath);
        QString nameOfEncryptedFolder = returnDirNameFromString(dirCleanedPath);
        QString relativePath = returnRelativPath(dirCleanedPath);


       // copyDropFiles(fileInfo2.absoluteFilePath(), nameOfEncryptedFolder, relativePath, fileInfo2);

}

void FileWindow::on_pushButton_decrypt_clicked()
{
/*
    QFileInfo fileInfo = QFileInfo(selectedDirPath);
    uCrypt::uCryptLib mainSession = log->getMainSession();
    qDebug() << TAG <<  "on_pushButton_decrypt_clicked: fileName: " << fileInfo.fileName() << " FilePath: " << fileInfo.absolutePath();

<<<<<<< HEAD
    //checkForErrors(mainSession.DecryptFile(fileInfo.fileName().toStdString(), fileInfo.absolutePath().toStdString()));
=======
    checkForErrors(mainSession.DecryptFile(fileInfo.fileName().toStdString(), fileInfo.absolutePath().toStdString()));
*/
    QString qSzFileName = QString(selectedDirPath);
    uCrypt::uCryptLib mainSession = login::GetInstance().getMainSession();
    qDebug() << TAG <<  "on_pushButton_decrypt_clicked: fileName: " << QFileInfo(qSzFileName).fileName() << " FilePath: " << QFileInfo(qSzFileName).absolutePath();

    checkForErrors(mainSession.DecryptFile(QFileInfo(qSzFileName).fileName().toStdString(), QFileInfo(qSzFileName).absolutePath().toStdString()));


}

void FileWindow::on_pushButton_sync_clicked()
{
    checkAndCopy();
}


void FileWindow::on_pushButton_syncCloud_clicked()
{
    checkAndCopyCloud();
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
        /*
        if(fileinfo.suffix() == "encrypted") {
            //Dateiendung entfernen für mehr Sicherheit?
            if (QFile::copy(from, toCloudDir + QDir::separator() + fileinfo.completeBaseName() + "." + fileinfo.suffix())) {
                QFile::remove(from);
                QFile::remove(toCloudDir + QDir::separator() + fileinfo.completeBaseName());
            }
        }
        else {
        */
            QFile::copy(from, toCloudDir + QDir::separator() + fileinfo.baseName() + "."  + fileinfo.suffix());
            QFile::copy(from, toWorkDir + QDir::separator() + fileinfo.baseName() + "."  + fileinfo.suffix());
        //}
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
        qDebug() << "filewindow deleteFile deleteCloudDir: " <<QFile::remove(deleteCloudDir + ".encrypted");
        qDebug() << "filewindow deleteFile deleteWorkDir: " <<QFile::remove(deleteWorkDir);
        qDebug() << "filewindow deleteFile deleteOriginals" <<QFile::remove(deleteOriginals);

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

bool FileWindow::isFileEncrypted(QString fileName, QString absolutePath)
{
    bool result = false;
    std::string fileInfoName = ".fileInfo";
    QFile qFileInfoName(absolutePath + QString::fromStdString("/_encrypted/") + QString::fromStdString(fileInfoName));

    if(qFileInfoName.exists())
    {
        if(!qFileInfoName.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QString errorM = qFileInfoName.errorString();
            QMessageBox::critical(this,"Disc Write fail", "Failed to write necessary files.\nError Details: " + errorM);
        }
        else
        {
            QTextStream fileContentStream(&qFileInfoName);
            QString s;

            while (! fileContentStream.atEnd())
            {
                QString strLine = fileContentStream.readLine();

                if(strLine.contains(fileName))
                {
                    // Line formating is FILENAME:HASH\n
                    QStringList stringlist_0;
                    stringlist_0 = strLine.split( ":" );

                    QString fName = stringlist_0[0];
                    QString fHash = stringlist_0[1];

                    QString originalFileHash = getEncodedHash(fileName, absolutePath);
                    if(originalFileHash == fHash)
                    {
                        // Original Hash equals the saved Hash in File -> no need to encrypt again
                        result = true;
                        s.append(strLine + "\n");
                    }
                    else
                    {
                        result = false;
                    }
                }
                else
                {
                    s.append(strLine + "\n");
                }
            }
            qFileInfoName.resize(0);
            fileContentStream << s;
            qFileInfoName.close();
        }
    }
    else
    {
        return result;
    }

    return result;
}

QString FileWindow::getEncodedHash(QString fileName, QString absolutPath)
{
    unsigned char bufHash[uCrypt::uCryptLib::_BLAKE2S_OUTBYTES];

    QFile file(absolutPath + QString("/") + fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        QString errorM = file.errorString();
        QMessageBox::critical(this,"Disc Write fail", "Failed to write necessary files.\nError Details: " + errorM);
    }

QByteArray buf = file.readAll();

    uCrypt::uCryptLib::blake2s_Hash(bufHash, buf.constData(), NULL, uCrypt::uCryptLib::_BLAKE2S_OUTBYTES, buf.size(), 0);

    std::string encodedHash = uCrypt::uCryptLib::base64_Encode(bufHash, uCrypt::uCryptLib::_BLAKE2S_OUTBYTES);

    return QString::fromStdString(encodedHash);
}

void FileWindow::checkAndCopy() {

    QThread *thread = new QThread();

    worker = new Worker();
    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()),this, SLOT(set_StatusBar_started()));
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()),this, SLOT(set_StatusBar_finished()));
    connect(worker, SIGNAL(finished()), this, SLOT(showErrorMessage()));
    //connect(worker, SIGNAL(finished()), this, SLOT(setCopyStatus()));
    thread->start();
}


void FileWindow::checkAndCopyCloud() {

    QThread *thread = new QThread();

    worker = new Worker();
    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()),this, SLOT(set_StatusBar_started()));
    connect(thread, SIGNAL(started()), worker, SLOT(processSyncCloud()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()),this, SLOT(set_StatusBar_finished()));
    //connect(worker, SIGNAL(finished()), this, SLOT(setCopyStatus()));
    thread->start();
}

void FileWindow::checkAndCopyAddButton(QString path) {

    QThread *thread = new QThread();

    Worker *worker2 = new Worker();
    worker2->moveToThread(thread);

    QSignalMapper *signalMapper = new QSignalMapper(0);
    connect(thread, SIGNAL(started()), signalMapper, SLOT(map()));

    signalMapper->setMapping(thread, path);

    connect(thread, SIGNAL(started()),this, SLOT(set_StatusBar_started()));
    connect(signalMapper, SIGNAL(mapped(QString)), worker2, SLOT(processAddFolder(QString)));
    connect(worker2, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker2, SIGNAL(finished()),this, SLOT(set_StatusBar_finished()));
    connect(worker2, SIGNAL(finished()), this, SLOT(showErrorMessage()));
    thread->start();
}

void FileWindow::set_StatusBar_finished(){

    qDebug() << "Window set_StatusBar_finished: sync done";
        ui->statusBar->removeWidget(syncWidget);
        ui->statusBar->addPermanentWidget(checkWidget, 0);
        checkWidget->show();
}

void FileWindow::set_StatusBar_started(){

    qDebug() << "Window set_StatusBar_started: start sync";
    ui->statusBar->removeWidget(checkWidget);
    ui->statusBar->addPermanentWidget(syncWidget, 0);
    syncWidget->show();

}

void FileWindow::handleModifiedFile(const QString & path){
    QString dirCleanedPath = returnDirectoryCleanedPath(path);
    QString nameOfEncryptedFolder = returnDirNameFromString(dirCleanedPath);
    QString relativePath = returnRelativPath(dirCleanedPath);

    QString toCloudDir = setman->returnSetting(MainWindow::settingsKeyForCloudDirPath, "clouddir") + QDir::separator() + nameOfEncryptedFolder + QDir::separator() + relativePath;
    fileshandler->copyFile(path, toCloudDir);

    watcher->removePath(path);
}


void FileWindow::on_pushButton_addFolder_clicked()
{
        QString folderPath = QFileDialog::getExistingDirectory(
                    this,
                    tr("Add folders to encrypt"),
                    "C://",
                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                    );

        checkAndCopyAddButton(folderPath);
}


void FileWindow::handleSelectionChanged(const QModelIndex& selection){

      QString selectedPath = filemodel->filePath(selection);
      qDebug() << selectedPath;

}

void FileWindow::showErrorMessage() {


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
