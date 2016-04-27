#ifndef STACKEDWINDOW_H
#define STACKEDWINDOW_H

#include <settingsmanager.h>

#include <QStackedWidget>
#include <QFileSystemModel>

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

namespace Ui {
class StackedWindow;
}

class StackedWindow : public QStackedWidget
{
    Q_OBJECT

public:
    explicit StackedWindow(QWidget *parent = 0);
    Ui::StackedWindow *ui;
    ~StackedWindow();

private:
    QFileSystemModel *fileBrowserModel;
    Settingsmanager *settingsmanager;

    QAction *act2,*act4;

    void initializeFileBrowser();
    void initializeTableWidget();
    void saveDirectories(QString name, QString path);
    void deleteDirectories(QString name);
    void populateTableWidget();

private slots:
    void pushZurueckManageClicked();
    void pushZurueckSettingsClicked();
    void pushDropboxClicked();
    void pushICloudClicked();
    void pushZurueckDropboxClicked();
    void pushZurueckICloudClicked();
    void pushAddClicked();
    void on_pushButton_addDir_clicked();


    void on_pushButton_deleteDir_clicked();

public slots:
    void pushSettingsClicked();
    void pushManageClicked();

};

#endif // STACKEDWINDOW_H
