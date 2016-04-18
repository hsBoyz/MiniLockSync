#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QSystemTrayIcon>
#include "filewindow.h"

class QAction;
class QMenu;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event);

public:
    Ui::MainWindow *ui;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void changeEvent(QEvent* evt);
    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();



    void on_btn_ok_dir_clicked();

private:
    //Ui::MainWindow *ui;


    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
    FileWindow *fileWindow;

    void createActions();
    void createTrayIcon();
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;


};

#endif // MAINWINDOW_H
