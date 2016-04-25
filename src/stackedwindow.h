#ifndef STACKEDWINDOW_H
#define STACKEDWINDOW_H

#include <QStackedWidget>

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
    ~StackedWindow();

private:
    Ui::StackedWindow *ui;

    QAction *act2,*act4;

private slots:
    void pushManageClicked();
    void pushSettingsClicked();
    void pushZurueckManageClicked();
    void pushZurueckSettingsClicked();

    void pushDropboxClicked();
    void pushICloudClicked();
    void pushZurueckDropboxClicked();
    void pushZurueckICloudClicked();
};

#endif // STACKEDWINDOW_H
