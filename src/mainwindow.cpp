#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "manage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Die Methode mit einem Ereignis verbinden
    connect(ui->pushManage, SIGNAL(clicked(bool)), SLOT(pushManageClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushManageClicked()
{   //Model approach
    Manage manage; //Object for manage class
    manage.setModal(true); //set manage window
    manage.exec(); //show dialog
}
