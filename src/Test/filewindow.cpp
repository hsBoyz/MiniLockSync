#include "filewindow.h"
#include "ui_filewindow.h"

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

    setFileModels();
    setListWidget();


}

FileWindow::~FileWindow()
{
    delete ui;
}

void FileWindow::setListWidget() {
    //filemodel_1 = new QFileSystemModel(this);
    //QString sPath1 = setman->returnSetting("directory", setman->getKeyAtPosition("directory", 0));
    //filemodel_1->setRootPath(sPath1);

    //ui->listWidget->setRootIndex(filemodel_1->index(sPath1));
    //ui->listWidget->


}

void FileWindow::setFileModels() {
    previousDirPath.clear();

    /*
     *
     *
     * NO dynamic implementation yet. sPath2 getKeyAtPosition
     *
     *
     *
    */
    filemodel_2 = new QFileSystemModel(this);
    QString sPath2 = setman->returnSetting("directory", setman->getKeyAtPosition("directory", 0));
    filemodel_2->setRootPath(sPath2);

    ui->listView_2->setModel(filemodel_2);
    ui->listView_2->setRootIndex(filemodel_2->index(sPath2));
    currentDirPath = sPath2;

    ui->label->setText(setman->getKeyAtPosition("directory", 0));
    //ui->label_2->setText(setman->getKeyAtPosition("directory", 0));
    ui->label_2->setText("Drag&Drop files to save in current dir");
}

void FileWindow::dragEnterEvent(QDragEnterEvent *e)
{
    e->acceptProposedAction();
    /*
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
    */

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


void FileWindow::on_pushButton_5_clicked()
{
    if (!previousDirPath.isEmpty()) {
        ui->listView_2->setRootIndex(filemodel_2->index(previousDirPath.last()));
        previousDirPath.removeLast();
    }
    selectedDirPath = "";

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
