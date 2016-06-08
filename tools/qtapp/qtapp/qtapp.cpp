#include "uCryptLib.h"
#include "qtapp.h"

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

#undef EncryptFile
#undef DecryptFile

qtApp::qtApp(QWidget *parent)
	: QDialog(parent)
{
	isInitialized = false;

	createActions();
    createTrayIcon();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
			 this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

	trayIcon->show();

	setIcon();

	setFixedSize(560,220);

	ui.setupUi(this);
}

qtApp::~qtApp()
{

}

void qtApp::setVisible(bool visible)
{
    QDialog::setVisible(visible);
}

void qtApp::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systray"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
        hide();
        event->ignore();
    }
}

void qtApp::setIcon()
{
    trayIcon->setIcon(QIcon(":/images/key.png"));
    setWindowIcon(QIcon(":/images/key.png"));
}

void qtApp::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
		
		if(isVisible())
			hide();
		else
			showNormal();

        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

void qtApp::createActions()
{
    encryptFolderAction = new QAction(tr("Encrypt &Folder"), this);
    connect(encryptFolderAction, SIGNAL(triggered()), this, SLOT(encryptFolderAction_click()));

    decryptFileAction = new QAction(tr("&Decrypt File"), this);
    connect(decryptFileAction, SIGNAL(triggered()), this, SLOT(decryptFileAction_click()));

	encryptFileAction = new QAction(tr("&Encrypt File"), this);
    connect(encryptFileAction, SIGNAL(triggered()), this, SLOT(encryptFileAction_click()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}


void qtApp::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(encryptFolderAction);
	trayIconMenu->addSeparator();
    trayIconMenu->addAction(decryptFileAction);
	trayIconMenu->addAction(encryptFileAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

void qtApp::loginButton_click()
{
	// check for entropy
	std::string password = ui.passwdLineEdit->text().toStdString();

	// double entropy_ar1 = uCrypt::uCryptLib::getBitEntropy("Die Wuerde des Menschen ist unantastbar.");
	double bitEntropy = uCrypt::uCryptLib::getBitEntropy(password);

	if ( ( bitEntropy * password.size() ) < 200)
	{
		QMessageBox::information(this, tr("Password too weak"),
                                 tr("Your password is too weak "
                                    "try to hit the \"Generate Password\" "
                                    "Button to generate a strong enough "
                                    "password from random words."));
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
		ui.comboBox->insertItem(0, identificationNumber);
	}
	
}

void qtApp::genPasswdButton_click()
{
	//wordlist.txt in directory
	QFile qFileWordList(QString("wordlist.txt"));

	if(!qFileWordList.exists())
	{
		QMessageBox::information(this, tr("Text File for Word Dictionary not found"),
			tr("Text File \"wordlist.txt\" for Word Dictionary not found! Check your working Directory!"));

	}
	else
	{
		if(!qFileWordList.open(QIODevice::ReadWrite | QIODevice::Text))
		{
			QString errorM = qFileWordList.errorString();
			QMessageBox::critical(this,"Disc Write fail", "Failed to write necessary files.\nError Details: " + errorM);
		}
		else
		{
			QString generatedString;
			QTextStream fileContentStream(&qFileWordList);
			QString s;

			while (! fileContentStream.atEnd())
			{
				QString strLine = fileContentStream.readLine();
				QStringList stringlist_0;
				stringlist_0 = strLine.split( "," );

				int min = 0, max = stringlist_0.size();

				for(int i=0; i < 8; i++)
				{
					int randNum = rand()%(max-min + 1) + min;
					if(i==0)
						generatedString = stringlist_0[randNum];
					else
						generatedString = generatedString + " " + stringlist_0[randNum];
				}
				break;
			}

			qFileWordList.close();
			ui.passwdLineEdit->setText(generatedString);
		}
	}
}

void qtApp::startButton_click()
{
	if(ui.yourIdLineEdit->text().isEmpty())
	{
		QMessageBox::information(this, tr("Application not initialized"),
                                 tr("Please enter a E-Mail Address and "
                                    "a Password before you try to start "
                                    "the Application "));
	}
	else
	{
		ui.recipientIdLineEdit->setReadOnly(true);
		QPalette *palette = new QPalette();
		palette->setColor(QPalette::Base, Qt::gray);
		palette->setColor(QPalette::Text, Qt::darkGray);
		ui.recipientIdLineEdit->setPalette(*palette);

		isInitialized = true;

		hide();
	}
}

void qtApp::addButton_click()
{
	ui.comboBox->insertItem(0, ui.recipientIdLineEdit->text());
}

void qtApp::decryptFileAction_click()
{
	if(isInitialized == false)
	{
		QMessageBox::information(this, tr("Application not initialized"),
			tr("Please enter a E-Mail Address and "
			"a Password before you try to start "
			"the Application "));
	}
	else
	{
		QString qSzFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
			"",
			tr("Files (*.encrypted)"));

		qDebug() << QFileInfo(qSzFileName).fileName();
		qDebug() << QFileInfo(qSzFileName).absolutePath();
		checkForErrors(mainSession.DecryptFile(QFileInfo(qSzFileName).fileName().toStdString(),
											   QFileInfo(qSzFileName).absolutePath().toStdString()));
	}
}

void qtApp::encryptFileAction_click()
{
	if(isInitialized == false)
	{
		QMessageBox::information(this, tr("Application not initialized"),
			tr("Please enter a E-Mail Address and "
			"a Password before you try to start "
			"the Application "));
	}
	else
	{
		QString qSzFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
			"",
			tr("Files (*.*)"));

		int numberOfRecipients = ui.comboBox->count();
		std::string *recipients = new std::string[numberOfRecipients];

		for(int i=0; i < numberOfRecipients; i++)
		{
			recipients[i] = ui.comboBox->itemText(i).toStdString();
		}

		checkForErrors(mainSession.EncryptFile(QFileInfo(qSzFileName).fileName().toStdString(),
											   QFileInfo(qSzFileName).absolutePath().toStdString(), 
											   recipients,
											   numberOfRecipients));
	}
}

void qtApp::checkForErrors(int result)
{
	switch(result)
	{
	case 1: // Encryption Error
		{
			QMessageBox::critical(this, tr("General Encryption Error"),
			tr("Library returned with the Error Code for a General Encryption Error!"));
			break;
		}

	case 2: // Decryption Error
		{
			QMessageBox::critical(this, tr("General Decryption Error"),
			tr("Library returned with the Error Code for a General Decryption Error!"));
			break;
		}

	case 3: // JSON Parsing Error
		{
			QMessageBox::critical(this, tr("General JSON Parsing Error"),
			tr("Library returned with the Error Code for a JSON Parsing Error!"));
			break;
		}

	case 4: // Invalid Header Version
		{
			QMessageBox::critical(this, tr("Invalid Header Version"),
			tr("Library returned with the Error Code for a Invalid Header Version!"));
			break;
		}

	case 5: // Invalid Sender
		{
			QMessageBox::critical(this, tr("Invalid Sender"),
			tr("Library returned with the Error Code for a Invalid Sender!"));
			break;
		}

	case 6: // Invalid Recipient
		{
			QMessageBox::critical(this, tr("Invalid Recipient"),
			tr("Library returned with the Error Code for a Invalid Recipient!"));
			break;
		}

	case 7: // Invalid File Hash
		{
			QMessageBox::critical(this, tr("Invalid File Hash"),
			tr("Library returned with the Error Code for a Invalid File Hash!"));
			break;
		}

	case 0xfe: // General File Read Error
		{
			QMessageBox::critical(this, tr("General File Read Error"),
			tr("Library returned with the Error Code for a File Read Error!"));
			break;
		}

	case 0xff: // Library not initialized
		{
			QMessageBox::critical(this, tr("Library not initialized"),
			tr("Library was called without beeing initialized correctly!"));
			break;
		}
	}
}

void qtApp::encryptFolderAction_click()
{
	if(isInitialized == false)
	{
		QMessageBox::information(this, tr("Application not initialized"),
			tr("Please enter a E-Mail Address and "
			"a Password before you try to start "
			"the Application "));
	}
	else
	{
		int numberOfRecipients = ui.comboBox->count();
		std::string *recipients = new std::string[numberOfRecipients];
		for(int i=0; i < numberOfRecipients; i++)
		{
			recipients[i] = ui.comboBox->itemText(i).toStdString();
		}


		QString qSzDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             "/home",
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);

		QDir dirWork(qSzDir);
		QFileInfoList files = dirWork.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::Files);
		
		QDir dirEncrypted(qSzDir + "/_encrypted");
		if(!(dirEncrypted.exists()))
			dirEncrypted.mkdir(".");

		for(int i = 0; i < files.count(); i++)
		{
			if (files[i].isFile())
			{
				if (! (isFileEncrypted(files[i].fileName(), 
									   files[i].absolutePath())))
				{
					qDebug() << files[i].fileName();
					qDebug() << dirWork.absolutePath();

					checkForErrors(mainSession.EncryptFile(files[i].fileName().toStdString(),
														   dirWork.absolutePath().toStdString(), 
														   recipients,
														   numberOfRecipients));

					qDebug() << dirWork.absolutePath() + QString("/") + files[i].fileName() + QString(".encrypted");
					QFile qFileNameEncrypted(dirWork.absolutePath() + QString("/") + files[i].fileName() + QString(".encrypted"));
					if(qFileNameEncrypted.exists())
					{
						qFileNameEncrypted.rename(dirEncrypted.absolutePath() + QString("/") +  files[i].fileName() + QString(".encrypted"));
					}

					std::string fileInfoName = ".fileInfo";
					QFile qFileInfoName(dirEncrypted.absolutePath() + QString("/")  + QString::fromStdString(fileInfoName));
					if(!qFileInfoName.open(QIODevice::Append))
					{
						QString errorM = qFileInfoName.errorString();
						QMessageBox::critical(this,"Disc Write fail", "Failed to write necessary files.\nError Details: " + errorM);
					}
					else
					{
						QTextStream out2(&qFileInfoName);
						out2 << files[i].fileName() << ":" << getEncodedHash(files[i].fileName(), dirWork.absolutePath()) << "\n";
						qFileInfoName.close();
					}

				}
			}
		}
	} 
}

bool qtApp::isFileEncrypted(QString fileName, QString absolutePath)
{
	bool result = false;
	std::string fileInfoName = ".fileInfo";
	QFile qFileInfoName(absolutePath + QString::fromStdString("/_encrypted/") + QString::fromStdString(fileInfoName));

	if(qFileInfoName.exists())
	{
		if(!qFileInfoName.open(QIODevice::ReadWrite | QIODevice::Text))
		{
			QString errorM = qFileInfoName.errorString();
			QMessageBox::critical(this,"Disc Write fail", "Failed to write necessary files.\nError Details: " + errorM);
		}
		else
		{
			QTextStream fileContentStream(&qFileInfoName);
			QString s;

			while (! fileContentStream.atEnd())
			{
				QString strLine = fileContentStream.readLine();

				if(strLine.contains(fileName))
				{
					// Line formating is FILENAME:HASH\n
					QStringList stringlist_0;
					stringlist_0 = strLine.split( ":" );

					QString fName = stringlist_0[0];
					QString fHash = stringlist_0[1];

					QString originalFileHash = getEncodedHash(fileName, absolutePath);
					if(originalFileHash == fHash)
					{
						// Original Hash equals the saved Hash in File -> no need to encrypt again
						result = true;
						s.append(strLine + "\n");
					}
					else
					{
						result = false;
					}
				}
				else
				{
					s.append(strLine + "\n");
				}
			}
			qFileInfoName.resize(0);
			fileContentStream << s;
			qFileInfoName.close();
		}
	}
	else
	{
		return result;
	}

	return result;
}

QString qtApp::getEncodedHash(QString fileName, QString absolutPath)
{
	unsigned char bufHash[uCrypt::uCryptLib::_BLAKE2S_OUTBYTES];

	QFile file(absolutPath + QString("/") + fileName);
	if(!file.open(QIODevice::ReadOnly))
	{
		QString errorM = file.errorString();
		QMessageBox::critical(this,"Disc Write fail", "Failed to write necessary files.\nError Details: " + errorM);
	}
	
QByteArray buf = file.readAll();

	uCrypt::uCryptLib::blake2s_Hash(bufHash, buf.constData(), NULL, uCrypt::uCryptLib::_BLAKE2S_OUTBYTES, buf.size(), 0);

	std::string encodedHash = uCrypt::uCryptLib::base64_Encode(bufHash, uCrypt::uCryptLib::_BLAKE2S_OUTBYTES);

	return QString::fromStdString(encodedHash);
}