#ifndef WINDOW_H
#define WINDOW_H

#include "settingsmanager.h"
#include "mainwindow.h"
#include "handlefiles.h"
#include "worker.h"
#include "timer.h"
#include "filewindow.h"
#include <QMainWindow>
#include <QFileSystemModel>
#include <QTableWidget>
#include <QFileDialog>

static int currentIndex = 0; // Global

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT


public:
    // >>> Singleton impl
    static Window &GetInstance() {
        static Window Instanz;
        return Instanz;
    }
    // <<<

    Ui::Window *ui;

    QAction *act1, *act2, *act3, *act4;

    void startAutoSync();

    ~Window();

public slots:
    void set_StatusBar_finished();
    void set_StatusBar_started();


protected:
    // void contextMenuEvent(QContextMenuEvent *event);


private slots:

    void on_pushHome_clicked();
    void on_pushCloudService_clicked();
    void on_pushManageCloud_clicked();
    void on_pushButton_addDir_clicked();
    void on_pushButton_deleteDir_clicked();
    void on_pushButton_addWorkDir_clicked();
    void on_pushManageSaveDir_clicked();
    void on_pushButton_deleteDir_2_clicked();
    void on_pushButton_confirm_clicked();
    void on_pushButton_AddCloud_clicked();
    void on_pushButton_delete_cloud_clicked();

    void menubar_instructions();
    void menubar_aboutus();

    void showErrorMessage();


private:
    // >>> Singleton impl
    Window(QWidget *parent = 0);
    Window(const Window&);
    Window &operator=(const Window&);
    // <<<

    QFileSystemModel *fileBrowserModel;
    Settingsmanager *settingsmanager;
    Handlefiles *filesHandler;
    Worker *worker;
    FileWindow *filewin;

    QLabel *checkWidget;
    QLabel *syncWidget;



    void initializeFileBrowser();
    void initializeTableWidget(QTableWidget *widget);
    void saveDirectories(QString group, QString name, QString path);
    void deleteDirectories(QString name);
    void populateTableWidget(QString group, QTableWidget *widget);
    QFileInfo returnSelectedPath();
    void copyDirectory();
    void checkAndCopy();



};

#endif // WINDOW_H
