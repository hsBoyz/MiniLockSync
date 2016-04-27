#ifndef WINDOW_H
#define WINDOW_H

#include "settingsmanager.h"
#include <QDialog>
#include <QFileSystemModel>

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

private:
    Ui::Window *ui;

    QFileSystemModel *fileBrowserModel;
    Settingsmanager *settingsmanager;

    void initializeFileBrowser();
    void initializeTableWidget();


};

#endif // WINDOW_H
