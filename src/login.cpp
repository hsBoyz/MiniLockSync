#include "login.hpp"
#include "uCryptLib.h"
#include "mainwindow.h"
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

	
MainWindow *mainWindow;

login::login(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
}

login::~login() {
	
}
void login::loginButton_click()
{
	// check for entropy
	std::string password = ui.passwdLineEdit->text().toStdString();

	// double entropy_ar1 = uCrypt::uCryptLib::getBitEntropy("Die Wuerde des Menschen ist unantastbar.");
	double bitEntropy = uCrypt::uCryptLib::getBitEntropy(password);

	if ((bitEntropy * password.size()) < 200)
	{
		QMessageBox::information(this, tr("Password too weak"),
			tr("Your password is too weak "));
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
		palette->setColor(QPalette::Base, Qt::gray);
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
			tr("Bitte geben Sie den Beutzernamen "
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
		mainWindow->show();
		
		
	}

}

void login::closeEvent(QCloseEvent *event)
{
	
		close();
		
	}
