#ifndef WINDOW_H
#define WINDOW_H

#include "settingsmanager.h"
#include "mainwindow.h"
#include <QDialog>
#include <QFileSystemModel>
#include <QTableWidget>

namespace Ui {
class Window;
}

class Window : public QDialog
{
    Q_OBJECT


public slots:



public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:

    void on_pushHome_clicked();

    void on_pushCloudService_clicked();

    void on_pushManageCloud_clicked();

    void on_pushCPULimitation_clicked();

    void on_pushChangePassword_clicked();

    void on_pushButton_addDir_clicked();
    void on_pushButton_deleteDir_clicked();

    void on_pushButton_addWorkDir_clicked();

    void on_pushButton_addSaveDir_clicked();

    void on_pushManageSaveDir_clicked();

    void on_pushButton_deleteDir_2_clicked();

private:
    Ui::Window *ui;

    QFileSystemModel *fileBrowserModel;
    Settingsmanager *settingsmanager;


    void initializeFileBrowser();
    void initializeTableWidget(QTableWidget *widget);
    void saveDirectories(QString group, QString name, QString path);
    void deleteDirectories(QString name);
    void populateTableWidget(QString group, QTableWidget *widget);
    QList<QString> returnSelectedPath();


};

#endif // WINDOW_H
