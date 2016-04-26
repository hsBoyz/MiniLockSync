#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QDialog>
#include <QFileSystemModel>
#include "settingsmanager.h"
#include "handlefiles.h"


namespace Ui {
class FileWindow;
}

class FileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FileWindow(QWidget *parent = 0);
    ~FileWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void setFileModels();

    void dragEnterEvent(QDragEnterEvent *e);
    void dragLeaveEvent(QDragEnterEvent *e);
    void dragMoveEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);


    void on_listView_2_doubleClicked(const QModelIndex &index);
    void on_pushButton_5_clicked();
    void on_listView_2_activated(const QModelIndex &index);
    void on_pushButton_6_clicked();

    void on_removeFile_clicked();

    void on_listView_2_clicked(const QModelIndex &index);

    void on_listView_saftyCopy_activated(const QModelIndex &index);

    void on_listView_saftyCopy_doubleClicked(const QModelIndex &index);

    void on_pushButton_backSaftyCopy_clicked();

    void on_listView_saftyCopy_clicked(const QModelIndex &index);

private:
    Ui::FileWindow *ui;
    QString TAG = "FILEWINDOW ";

    QFileSystemModel *filemodel_2;
    QFileSystemModel *filemodel_saftycopy;
    Settingsmanager *setman;
    //HandleFiles *filesHandler;

    QList<QString> previousDirPath;     //List for storing the file browsing history
    QString currentDirPath;             //current path of directory for copying files
    QString selectedDirPath = "";

    QList<QString> previousDirPathWorkDir;
    QString currentDirPathWorkDir;
    QString selectedDirPathWorkDir = "";


    QString returnDirectoryCleanedPath(QString);

};

#endif // FILEWINDOW_H
