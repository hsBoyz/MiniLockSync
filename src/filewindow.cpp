#include "filewindow.h"
#include "ui_filewindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDesktopServices>

FileWindow::FileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    setman = new Settingsmanager();
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
    previousDirPath.append(filemodel->fileInfo(index).absolutePath());
}

void FileWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    if (filemodel->fileInfo(index).isDir()) {
        //Step into folder
        ui->listView->setRootIndex(index);
    }
    else {
        //Open document with system standard application
        QDesktopServices::openUrl(filemodel->fileInfo(index).absoluteFilePath());
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

    qDebug() << "filewindow setfilemodels spath: " << sPath1;

    filemodel->setRootPath(sPath1);

    ui->listView->setModel(filemodel);
    ui->listView->setRootIndex(filemodel->index(sPath1));


    //ui->label->setText(setman->getKeyAtPosition(MainWindow::settingsKeyForPaths, 0));

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
    /*
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
    */
}


