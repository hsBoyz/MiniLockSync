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

#include "stackedwindow.h"
#include "window.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QTextEdit* editor;
    QTextEdit* dock_editor;

    static QString settingsKeyForPaths;



    ~MainWindow();


public slots:
    void search();

protected:
     void contextMenuEvent(QContextMenuEvent *event);

private:
    Ui::MainWindow *ui;

    StackedWindow *stackedwin;

    QAction *act2,*act4;


private slots:
    void pushConfirmClicked();

    void on_pushSecondInterface_clicked();
};

#endif // MAINWINDOW_H
