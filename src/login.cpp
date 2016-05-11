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

	
MainWindow *mainWindow;

login::login(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
    loadLogin();
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
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    palette->setColor(QPalette::Text, Qt::black);

    ui.passwdLineEdit->setPalette(*palette);
    ui.eMailLineEdit->setPalette(*palette);



}



void login::saveLogin()
{
    if(ui.saveLogin->isChecked())
    {


         QSettings setting("MyApp","mysetting");
         setting.beginGroup("login");
         setting.setValue("logName",this->ui.eMailLineEdit->text());
         setting.setValue("logPassword",this->ui.passwdLineEdit->text());
         setting.setValue("check",this->ui.saveLogin->isChecked());
         setting.endGroup();



    }
    else
    {
        QSettings setting("MyApp","mysetting");
        setting.clear();
    }
}

void login::loadLogin()
{
    QSettings setting("MyApp","mysetting");
    setting.beginGroup("login");
    QString qSzEmail = setting.value("logName").toString();
    QString qSzPasswd = setting.value("logPassword").toString();

    ui.eMailLineEdit->setText(qSzEmail);
    ui.passwdLineEdit->setText(qSzPasswd);
    ui.saveLogin->setChecked(true);
   if(qSzEmail != 0)
    loginButton_click();
else
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
		QMessageBox::information(this, tr("Passwort zu schwach"),
			tr("Das Passwort muss midestens 8 Zeichen lang sein. "));
	}
	else
	{
        mainSession.uCryptInit(ui.eMailLineEdit->text().toStdString(),
            ui.passwdLineEdit->text().toStdString());

		ui.passwdLineEdit->setEchoMode(QLineEdit::Password);

		QString qSzPasswd = ui.passwdLineEdit->text();
		QString qSzEmail = ui.eMailLineEdit->text();

		ui.passwdLineEdit->setReadOnly(true);
		ui.eMailLineEdit->setReadOnly(true);

		QPalette *palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::lightGray);
        palette->setColor(QPalette::Text, Qt::darkGray);

		ui.passwdLineEdit->setPalette(*palette);
        ui.eMailLineEdit->setPalette(*palette);

        QString identificationNumber = QString::fromStdString(mainSession.getIdentificationNumber());

		ui.yourIdLineEdit->setText(identificationNumber);
		
	}

}
void login::startButton_click()
{
	if (ui.yourIdLineEdit->text().isEmpty())
	{
		QMessageBox::information(this, tr("Fehler"),
			tr("Bitte geben Sie den Benutzernamen "
				"und das Passwort ein um nach  "
				"dem Login das Programm zu starten "));
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
