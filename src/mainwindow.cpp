#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "window.h"
//#include "ui_window.h"

#include <QApplication>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QVariant>
#include <QFontComboBox>
#include <QCloseEvent>

QString MainWindow::settingsKeyForPaths = "directory";
QString MainWindow::settingsKeyForWorkDirPath = "workdirectory";
QString MainWindow::settingsKeyGeneralSettings = "general";
QString MainWindow::settingsKeyForCloudDirPath = "clouddirectory";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);




}

MainWindow::~MainWindow()
{
    delete ui;


}








void MainWindow::on_pushSecondInterface_clicked()
{
    /*
    //Model approach (dealing with stack memory)
    Window window;    //creat object stackedwindow
    window.setModal(false);   //use object to open second window
    window.exec();           //show second window
    //window.show();
    */

    Window::GetInstance().show();
    //window->show();
}
