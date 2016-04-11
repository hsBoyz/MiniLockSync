 #include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString sPath = "C:/";
    dirmodel = new QFileSystemModel (this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(sPath);

    ui->treeView->setModel(dirmodel);

    QStringList title;
    title << "Pfad" << "Name";
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(title);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();
    //ui->listWidget->addItem(sPath);
}

void MainWindow::on_pushButton_clicked()
{
    QString sPath = dirmodel->fileInfo(ui->treeView->currentIndex()).absolutePath() + "/" + dirmodel->fileInfo(ui->treeView->currentIndex()).baseName();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(dirmodel->fileInfo(ui->treeView->currentIndex()).absolutePath()));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(dirmodel->fileInfo(ui->treeView->currentIndex()).baseName()));

}
