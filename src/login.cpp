#include "login.hpp"
#include "uCryptLib.h"
#include "mainwindow.h"
#include "filewindow.h"
#include "steerer.h"
#include "settingsmanager.h"

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
#include <QDebug>

	
MainWindow *mainWindow;

login::login(QWidget * parent) : QWidget(parent) {
    ui.setupUi(this);
    this->userExists = false;
    connect(ui.eMailLineEdit, SIGNAL (editingFinished()), this, SLOT(checkUserName()));
    connect(ui.saveLogin, SIGNAL(stateChanged(int)), this, SLOT(saveLogin_click(int)));

    Settingsmanager *setman = new Settingsmanager();

    if (setman->returnSetting("general", "check") == "true") {
        loadLogin(setman->returnSetting("general", "user"));
        qDebug() <<  "login loaded";
    }






   // QRegExp rx("^(?![^a-zA-Z]*$|[^a-z0-9]*$|[^a-z<+$*]*$|[^A-Z0-9]*$|[^A-Z<+$*]*$|[^0-9<+$*]*$|.*[|;{}]).*$");

    ui.yourIdLineEdit->setReadOnly(true);
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::lightGray);
    palette->setColor(QPalette::Text, Qt::darkGray);

    ui.yourIdLineEdit->setPalette(*palette);
    ui.passwdLineEdit->setEchoMode(QLineEdit::Password);
    ui.conPWlineEdit->setEchoMode(QLineEdit::Password);

    //delete(setman);

}


login::~login() 
{
	
}


uCrypt::uCryptLib login::mainSession = uCrypt::uCryptLib();
bool login::isInitialized = false;
QString login::user = "";

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

    ui.conPWlineEdit->setEnabled(true);

    this->user = "";
    this->userExists = false;

    disconnect(ui.passwdLineEdit, SIGNAL (cursorPositionChanged(int, int)), this, SLOT(setConPasswd()));


}



void login::saveLogin()
{
    //if(ui.saveLogin->isChecked())
    //{


         QSettings setting("MyApp","mysetting");
         setting.beginGroup(this->ui.eMailLineEdit->text());
         setting.beginGroup("login");
         setting.setValue("logName",this->ui.eMailLineEdit->text());
         setting.setValue("logPassword",this->ui.passwdLineEdit->text());
         setting.setValue("conPW",this->ui.conPWlineEdit->text());
         setting.setValue("check",this->ui.saveLogin->isChecked());
         setting.setValue("lineEdit",this->ui.yourIdLineEdit->text());
         setting.setValue("checkbox",this->ui.comboBox->itemText(0));
         setting.endGroup();
         setting.endGroup();
/*
    }
    else
    {
        QSettings setting("MyApp","mysetting");
        setting.beginGroup("login");
        setting.clear();
        setting.endGroup();
    }
    */
}

void login::loadLogin(QString user)
{
    QSettings setting("MyApp","mysetting");
    setting.beginGroup(user);
    setting.beginGroup("login");
    QString qSzEmail = setting.value("logName").toString();
    QString qSzPasswd = setting.value("logPassword").toString();
    QString conPW = setting.value("conPW").toString();
    QString idNumber = setting.value("lineEdit").toString();
    QString checkbox = setting.value("checkbox").toString();


    ui.eMailLineEdit->setText(qSzEmail);
    ui.passwdLineEdit->setText(qSzPasswd);
    ui.conPWlineEdit->setText(conPW);
    ui.saveLogin->setChecked(true);
    ui.yourIdLineEdit->setText(idNumber);
    ui.comboBox->setItemText(0, checkbox);

     setting.endGroup();
     setting.endGroup();
     loginButton_click();

    qDebug()<<  "load complete";

/*
    if(checkbox == idNumber)
    {
        autostart();
    }
    else
        loginButton_click();
*/

}

void login::saveLogin_click(int check)

{
    if (check == 2 || check == 1) {
        qDebug() << "login savelogin_click: checked";
        QSettings setting("MyApp","mysetting");
        setting.beginGroup("general");
        setting.remove("check");
        setting.setValue("check","true"); //Store in general settings, not user specific
        setting.setValue("user", ui.eMailLineEdit->text());
        setting.endGroup();
    }
    else {
        qDebug() << "login savelogin_click: unchecked";
        QSettings setting("MyApp","mysetting");
        setting.beginGroup("general");
        setting.remove("check");
        setting.setValue("check","false"); //Store in general settings, not user specific
        setting.setValue("user", ui.eMailLineEdit->text());
        setting.endGroup();
    }

}




void login::loginButton_click()
{
    QSettings setting("MyApp","mysetting");
    setting.beginGroup("general");
    setting.remove("user");
    setting.setValue("user", ui.eMailLineEdit->text());
    setting.endGroup();

    if (this->userExists) {
        if (checkPassword() == false) {

        }
        else
        {
            loginDataConfirmed();
        }
    }

    else if (!this->userExists){

        //regexp for checking PW complexity
           QString checkPasswd = ui.passwdLineEdit->text();
           QRegularExpression rx("^(?![^a-zA-Z]*$|[^a-z0-9]*$|[^a-z<+$*]*$|[^A-Z0-9]*$|[^A-Z<+$*]*$|[^0-9<+$*]*$|.*[|;{}]).*$");
          //QRegularExpression rx(" ^(?:(?=.*[0-9])(?=.*[a-z])(?=.*[<+$*)])|(?=.*[a-z])(?=.*[<+$*)])(?=.*[A-Z])|(?=.*[0-9])(?=.*[A-Z])(?=.*[<+$*)])|(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z]))(?!.*[|;{}].*$).+$");
           QRegularExpressionMatch rmatch = rx.match(checkPasswd);

            QString checkLog = ui.eMailLineEdit->text();
            QRegularExpression rc("[a-z]|[A-Z]|[0-9]");
             QRegularExpressionMatch logmatch = rc.match(checkLog);


        // check for entropy
        std::string password = ui.passwdLineEdit->text().toStdString();


        // double entropy_ar1 = uCrypt::uCryptLib::getBitEntropy("Die Wuerde des Menschen ist unantastbar.");
        double bitEntropy = uCrypt::uCryptLib::getBitEntropy(password);


        if(logmatch.hasMatch() == 0)
        {
               QMessageBox::information(this, tr("Wrong Login"),
                   tr("Please enter a valid login, containing only characters and numbers. "));

        }
        else if(rmatch.hasMatch() == 0)
        {
            QMessageBox::information(this, tr("Password too weak"),
                tr("The password should at least have one digit,"
                   " one capital letter or one special letter"
                   " . "));
        }
        else if ((bitEntropy * password.size()) < 24) // war auf 200... übertrieben?
        {
            QMessageBox::information(this, tr("Password to weak"),
                tr("Password should be atleast 8 characters. "));
        }
        else if( ui.passwdLineEdit->text() != ui.conPWlineEdit->text())
        {
            QMessageBox::information(this, tr("Wrong Password"),
                tr("Passwords dont match. "));

        }
        else {
            loginDataConfirmed();
        }

    }


}
void login::startButton_click()
{

	if (ui.yourIdLineEdit->text().isEmpty())
	{
        QMessageBox::information(this, tr("Error"),
            tr("Please generate a key first "
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

        Window::GetInstance().show();
       // FileWindow::GetInstance().show();

       Steerer::GetInstance().start();
       qDebug()<<  "startbutton clicked";

       Settingsmanager *setman = new Settingsmanager();
       if (setman->keyExists(MainWindow::settingsKeyForWorkDirPath, "workdir") && setman->keyExists(MainWindow::settingsKeyForCloudDirPath, "clouddir")) {
           Timer::GetInstance().stop();
           Timer::GetInstance().start();
       }

		
	}


}

/*
  void login::autostart()
{


    isInitialized = true;
    Steerer::GetInstance().start();

    qDebug()<<  "autostart engaged";
}
*/

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

void login::checkUserName() {
    qDebug() << "Login checkusername: user exists: " << this->userExists;
    Settingsmanager *setman = new Settingsmanager();
    if (ui.eMailLineEdit->text() != "") {
        if (setman->groupExists(ui.eMailLineEdit->text())) {
            qDebug() << "group exists: " << setman->groupExists(ui.eMailLineEdit->text());
            ui.conPWlineEdit->setEnabled(false);
            this->userExists = true;
            connect(ui.passwdLineEdit, SIGNAL (editingFinished()), this, SLOT(enableLoginButton()));
            connect(ui.passwdLineEdit, SIGNAL (cursorPositionChanged(int, int)), this, SLOT(setConPasswd()));

            //delete(setman);
        }
    }
    //delete(setman);
}

bool login::checkPassword() {
    QSettings setting("MyApp","mysetting");
    setting.beginGroup(ui.eMailLineEdit->text());
    setting.beginGroup("login");
    QString qSzPasswd = setting.value("logPassword").toString();

    if (ui.passwdLineEdit->text() == qSzPasswd) {
        return true;
    }
    else {
        ui.loginButton->setEnabled(false);
        QMessageBox msgBox;
        msgBox.setInformativeText(tr("Wrong password or username"));
        msgBox.exec();
        ui.passwdLineEdit->setFocus();
        ui.passwdLineEdit->selectAll();


        return false;
    }
}

void login::loginDataConfirmed() {
    mainSession.uCryptInit(ui.eMailLineEdit->text().toStdString(),
        ui.passwdLineEdit->text().toStdString());



    QString qSzPasswd = ui.passwdLineEdit->text();
    QString qSzEmail = ui.eMailLineEdit->text();
    QString conPW = ui.conPWlineEdit->text();

    this->user = qSzEmail;

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

    saveLogin();    //Save login data in settings


}

void login::enableLoginButton() {
    ui.loginButton->setEnabled(true);
    ui.loginButton->setFocus();
}

void login::setConPasswd() {
    ui.conPWlineEdit->clear();
    ui.conPWlineEdit->setText(ui.passwdLineEdit->text());
}

