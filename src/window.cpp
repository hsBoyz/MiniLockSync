#include "window.h"
#include "ui_window.h"


Window::Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);



     //Verbinde Ereignis mit Methode
     connect (ui->pushHome, SIGNAL(clicked(bool)), SLOT(on_pushHome_clicked()));
     connect (ui->pushCloudService, SIGNAL(clicked(bool)), SLOT(on_pushCloudService_clicked()));
     connect (ui->pushManageCloud, SIGNAL(clicked(bool)), SLOT(on_pushManageCloud_clicked()));
     connect (ui->pushCPULimitation, SIGNAL(clicked(bool)), SLOT(on_pushCPULimitation_clicked()));
     connect (ui->pushChangePassword, SIGNAL(clicked(bool)), SLOT(on_pushChangePassword_clicked()));

}

Window::~Window()
{
    delete ui;
}


void Window::on_pushHome_clicked()
{
    ui->Home->show();
    ui->CloudService->hide();
    ui->ManageCloud->hide();
    ui->CPULimitation->hide();
    ui->ChangePasword->hide();
}
void Window::on_pushCloudService_clicked()
{
    ui->CloudService->show();
    ui->Home->hide();
    ui->ManageCloud->hide();
    ui->CPULimitation->hide();
    ui->ChangePasword->hide();
}

void Window::on_pushManageCloud_clicked()
{
    ui->ManageCloud->show();
    ui->Home->hide();
    ui->CloudService->hide();
    ui->CPULimitation->hide();
    ui->ChangePasword->hide();
}

void Window::on_pushCPULimitation_clicked()
{
    ui->CPULimitation->show();
    ui->Home->hide();
    ui->CloudService->hide();
    ui->ManageCloud->hide();
    ui->ChangePasword->hide();
}

void Window::on_pushChangePassword_clicked()
{
    ui->ChangePasword->show();
    ui->Home->hide();
    ui->CloudService->hide();
    ui->ManageCloud->hide();
    ui->CPULimitation->hide();
}


