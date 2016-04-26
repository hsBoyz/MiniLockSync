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
    //filesHandler = new HandleFiles();

    //createCopyAndWorkDir();
    //copyDirectory();
    setFileModels();



}

FileWindow::~FileWindow()
{
    delete ui;
}

void FileWindow::setFileModels() {
    previousDirPath.clear();

    filemodel_saftycopy = new QFileSystemModel(this);
    //QString sPath1 = setman->returnSetting(MainWindow::settingsKeyForSaveDir, "mainfolder");      //This displays workplace and savetycopy
    QString sPath1 = setman->returnSetting(MainWindow::settingsKeyForSaveDir, "workplace");
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

    qDebug() << TAG << "setfilesmodels Path " << sPath2;


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
    QString path = returnDirectoryCleanedPath(currentDirPath);
    if (e->mimeData()->hasUrls()) {
        foreach (QUrl url, e->mimeData()->urls()) {
            qDebug() << path;
            qDebug() << setman->returnSetting(MainWindow::settingsKeyForSaveDir, "workplace") + "/" + path + "/" + url.fileName();
            qDebug() << TAG + " dropEvent, File copied? " << QFile::copy(url.toLocalFile(), (setman->returnSetting(MainWindow::settingsKeyForSaveDir, "workplace")
                                                                                                                                  + "/" + path + "/" + url.fileName()));
            qDebug() << TAG + " dropEvent, File copied to workdir? " << QFile::copy(url.toLocalFile(),
                                (setman->returnSetting(MainWindow::settingsKeyForPaths, setman->getKeyAtPosition("directory", 0)) + "/" + path + "/" + url.fileName()));

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

    QString path = returnDirectoryCleanedPath(selectedDirPath);

    if (path != "") {
        int returnValue = msgBox.exec();

        switch (returnValue) {
            case QMessageBox::Ok:
                QFile::remove(setman->returnSetting(MainWindow::settingsKeyForSaveDir, "workplace") + "/" + path);
                QFile::remove(setman->returnSetting(MainWindow::settingsKeyForSaveDir, "safetycopy") + "/" + path);
                QFile::remove(setman->returnSetting(MainWindow::settingsKeyForPaths, setman->getKeyAtPosition("directory", 0)) + "/" + path);
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

void FileWindow::on_listView_saftyCopy_clicked(const QModelIndex &index)
{
    selectedDirPath = filemodel_saftycopy->fileInfo(index).absoluteFilePath();
}

QString FileWindow::returnDirectoryCleanedPath(QString path) {
    int layers;
    QString returnPath;

    //count folder-layers user moved in for getting path later
    if (path.contains("Workplace")) {
       layers = previousDirPathWorkDir.length() + 1;
    }
    else {
       layers = previousDirPath.length() + 1;
    }

    return returnPath = path.section("/", -layers);
}
