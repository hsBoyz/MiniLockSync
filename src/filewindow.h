#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include "handlefiles.h"
#include <QMainWindow>
#include <QFileSystemModel>
#include <settingsmanager.h>

namespace Ui {
class FileWindow;
}

class FileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileWindow(QWidget *parent = 0);
    ~FileWindow();

private slots:
    void setFileModels();
    QString returnDirectoryCleanedPath(QString path);
    QString returnDirNameFromString(QString path);
    QString returnRelativPath(QString path);
    void copyDropFiles(QString from, QString folderName, QString relativePath, QFileInfo fileinfo);
    void deleteFile(QString folderName, QString relativePath);

    void dragEnterEvent(QDragEnterEvent *e);
    void dragLeaveEvent(QDragLeaveEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent(QDropEvent *e);

    void on_pushButton_back_clicked();
    void on_listView_activated(const QModelIndex &index);
    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pushButton_deleteFile_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::FileWindow *ui;

    QFileSystemModel *filemodel;
    Settingsmanager *setman;
    Handlefiles *fileshandler;

    QString keyOfCurrentFileBrowser;    //Necessary to load different filewindows, e.g. for each encrypted folder
    QList<QString> previousDirPath;     //List for storing the file browsing history
    QString currentDirPath;             //current path of directory for copying files
    QString selectedDirPath = "";
};

#endif // FILEWINDOW_H
