#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QTextEdit>
#include <QContextMenuEvent>
#include <QFont>
#include <QFile>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QStatusBar>
#include <QLabel>
#include <QLCDNumber>
#include <QDateTime>
#include <QProgressBar>
#include <QToolBar>
#include <QDockWidget>
#include <QSettings>

#include "window.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);


    static QString settingsKeyForPaths;
    static QString settingsKeyForWorkDirPath;
    static QString settingsKeyForSaveDirPath;
    static QString settingsKeyGeneralSettings;

    ~MainWindow();


public slots:


protected:
     void contextMenuEvent(QContextMenuEvent *event);

private:
    Ui::MainWindow *ui;

    QAction *act1,*act2,*act3,*act4;



private slots:
    void pushConfirmClicked();

    void on_pushSecondInterface_clicked();
};

#endif // MAINWINDOW_H
