#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include "handlefiles.h"
#include "login.hpp"
#include "ui_login.h"
#include "worker.h"
#include <QMainWindow>
#include <QFileSystemModel>
#include <settingsmanager.h>
#include <uCryptLib.h>
#include <QThread>
#include <QFileSystemWatcher>

namespace Ui {
class FileWindow;
}

class FileWindow : public QMainWindow
{
    Q_OBJECT

public:
    // >>> Singleton impl
    static FileWindow &GetInstance() {
        static FileWindow Instanz;
        return Instanz;
    }

    // <<<

    ~FileWindow();
    void addPathToWatcher(QString path);


private slots:
    void setFileModels();
    QString returnDirectoryCleanedPath(QString path);
    QString returnDirNameFromString(QString path);
    QString returnRelativPath(QString path);
    void copyDropFiles(QString from, QString folderName, QString relativePath, QFileInfo fileinfo);
    void fileExists(QString path, QFileInfo fileInfo);
    void deleteFile(QString folderName, QString relativePath, QFileInfo fileInfo);
    void checkForErrors(int result);
    void handleModifiedFile(const QString &path);
    void handleSelectionChanged(const QModelIndex &selection);

    void dragEnterEvent(QDragEnterEvent *e);
    void dragLeaveEvent(QDragLeaveEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent(QDropEvent *e);

    void on_pushButton_back_clicked();
    void on_listView_activated(const QModelIndex &index);
    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pushButton_deleteFile_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_pushButton_encrypt_clicked();

    void on_pushButton_decrypt_clicked();

    void on_pushButton_sync_clicked();

    void on_pushButton_syncCloud_clicked();

    void on_pushButton_addFolder_clicked();

public slots:
    void set_StatusBar_finished();
    void set_StatusBar_started();

private:
    // >>> Singleton impl
    FileWindow(QWidget *parent = 0);
    FileWindow(const FileWindow&);
    FileWindow &operator=(const FileWindow&);
    // <<<

    QString TAG = "Filewindow ";

    Ui::FileWindow *ui;

    QLabel *checkWidget;
    QLabel *syncWidget;

    QFileSystemModel *filemodel;
    Settingsmanager *setman;
    Handlefiles *fileshandler;
    Worker *worker;

    QFileSystemWatcher *watcher;

    QString keyOfCurrentFileBrowser;    //Necessary to load different filewindows, e.g. for each encrypted folder
    QList<QString> previousDirPath;     //List for storing the file browsing history
    QString currentDirPath;             //current path of directory for copying files
    QString selectedDirPath = "";

    bool isFileEncrypted(QString fileName, QString absolutePath);
    QString getEncodedHash(QString fileName, QString absolutPath);
    void checkAndCopy();
    void checkAndCopyCloud();
};

#endif // FILEWINDOW_H
