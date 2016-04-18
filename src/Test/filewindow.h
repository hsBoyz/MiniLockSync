#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QDialog>
#include <QFileSystemModel>
#include "settingsmanager.h"


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

private:
    Ui::FileWindow *ui;

    QFileSystemModel *filemodel_1;
    QFileSystemModel *filemodel_2;
    Settingsmanager *setman;

};

#endif // FILEWINDOW_H
