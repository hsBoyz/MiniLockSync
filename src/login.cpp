#include "login.hpp"
#include "uCryptLib.h"
#include "mainwindow.h"
#include "filewindow.h"
#include "steerer.h"
//#include "settingsmanager.h"

#include <QtGui>
#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <random>
#include <QSettings>
#include <QRegExp>

	
MainWindow *mainWindow;

login::login(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
    loadLogin();


   // QRegExp rx("^(?![^a-zA-Z]*$|[^a-z0-9]*$|[^a-z<+$*]*$|[^A-Z0-9]*$|[^A-Z<+$*]*$|[^0-9<+$*]*$|.*[|;{}]).*$");

    ui.yourIdLineEdit->setReadOnly(true);
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::lightGray);
    palette->setColor(QPalette::Text, Qt::darkGray);

    ui.yourIdLineEdit->setPalette(*palette);
    ui.passwdLineEdit->setEchoMode(QLineEdit::Password);
    ui.conPWlineEdit->setEchoMode(QLineEdit::Password);


}


login::~login() 
{
	
}


uCrypt::uCryptLib login::mainSession = uCrypt::uCryptLib();
bool login::isInitialized = false;

void login::cancelButton_click()
{

    ui.passwdLineEdit->setReadOnly(false);
    ui.eMailLineEdit->setReadOnly(false);
    ui.conPWlineEdit->setReadOnly(false);
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    palette->setColor(QPalette::Text, Qt::black);

    ui.passwdLineEdit->setPalette(*palette);
    ui.eMailLineEdit->setPalette(*palette);
    ui.conPWlineEdit->setPalette(*palette);



}



void login::saveLogin()
{
    if(ui.saveLogin->isChecked())
    {


         QSettings setting("MyApp","mysetting");
         setting.beginGroup("login");
         setting.setValue("logName",this->ui.eMailLineEdit->text());
         setting.setValue("logPassword",this->ui.passwdLineEdit->text());
         setting.setValue("conPW",this->ui.conPWlineEdit->text());
         setting.setValue("check",this->ui.saveLogin->isChecked());
         setting.endGroup();



    }
    else
    {
        QSettings setting("MyApp","mysetting");
        setting.beginGroup("login");
        setting.clear();
        setting.endGroup();
    }
}

void login::loadLogin()
{
    QSettings setting("MyApp","mysetting");
    setting.beginGroup("login");
    QString qSzEmail = setting.value("logName").toString();
    QString qSzPasswd = setting.value("logPassword").toString();
    QString conPW = setting.value("conPW").toString();

    ui.eMailLineEdit->setText(qSzEmail);
    ui.passwdLineEdit->setText(qSzPasswd);
    ui.conPWlineEdit->setText(conPW);
    ui.saveLogin->setChecked(true);
   if(qSzEmail != 0)
    loginButton_click();

    setting.endGroup();



}

void login::saveLogin_click()

{

    saveLogin();

}


void login::loginButton_click()
{
	// check for entropy
	std::string password = ui.passwdLineEdit->text().toStdString();


	// double entropy_ar1 = uCrypt::uCryptLib::getBitEntropy("Die Wuerde des Menschen ist unantastbar.");
	double bitEntropy = uCrypt::uCryptLib::getBitEntropy(password);

    if ((bitEntropy * password.size()) < 10) // war auf 200... übertrieben?
	{
        QMessageBox::information(this, tr("Password to wea"),
            tr("Password should be atleast 8 characters. "));
	}

    else if( ui.passwdLineEdit->text() != ui.conPWlineEdit->text())
    {
        QMessageBox::information(this, tr("Wrong Password"),
            tr("Passwords dont match. "));


    }


	else
	{
        mainSession.uCryptInit(ui.eMailLineEdit->text().toStdString(),
            ui.passwdLineEdit->text().toStdString());



		QString qSzPasswd = ui.passwdLineEdit->text();
		QString qSzEmail = ui.eMailLineEdit->text();
        QString conPW = ui.conPWlineEdit->text();

		ui.passwdLineEdit->setReadOnly(true);
		ui.eMailLineEdit->setReadOnly(true);
        ui.conPWlineEdit->setReadOnly(true);

		QPalette *palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::lightGray);
        palette->setColor(QPalette::Text, Qt::darkGray);

		ui.passwdLineEdit->setPalette(*palette);
        ui.eMailLineEdit->setPalette(*palette);
        ui.conPWlineEdit->setPalette(*palette);

        QString identificationNumber = QString::fromStdString(mainSession.getIdentificationNumber());

		ui.yourIdLineEdit->setText(identificationNumber);
        ui.comboBox->insertItem(0, identificationNumber);
	}

}
void login::startButton_click()
{
	if (ui.yourIdLineEdit->text().isEmpty())
	{
        QMessageBox::information(this, tr("Error"),
            tr("Please log in first "
                "to start the program " ));
	}
	else
    {


        QPalette *palette = new QPalette();
		palette->setColor(QPalette::Base, Qt::gray);
		palette->setColor(QPalette::Text, Qt::darkGray);
		

		isInitialized = true;

		hide();
        mainWindow = new MainWindow(this);
	//	mainWindow->show();
		Window *window = new Window();
		window->show();

        Steerer *s = new Steerer();
        s->start();


		
	}

}

void login::closeEvent(QCloseEvent *event)
{

       QWidget::closeEvent(event);
}

uCrypt::uCryptLib login::getMainSession() {
    return this->mainSession;
}

bool login::getIsInitialized() {
    return this->isInitialized;
}
