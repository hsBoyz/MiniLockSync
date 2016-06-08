#ifndef QTAPP_H
#define QTAPP_H

#include <QtWidgets/QDialog>
#include <QSystemTrayIcon>
#include "ui_qtapp.h"
#include <uCryptLib.h>


class qtApp : public QDialog
{
	Q_OBJECT

public:
	qtApp(QWidget *parent = 0);
	~qtApp();
	void setVisible(bool visible);

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void setIcon();
	void iconActivated(QSystemTrayIcon::ActivationReason reason);

	void loginButton_click();
	void genPasswdButton_click();
	void startButton_click();
	void addButton_click();

	void encryptFolderAction_click();
	void decryptFileAction_click();
	void encryptFileAction_click();

private:
	uCrypt::uCryptLib mainSession;
	void checkForErrors(int r);
	bool isFileEncrypted(QString fileName, QString absolutePath);
	QString getEncodedHash(QString fileName, QString absolutPath);

	bool isInitialized;

	Ui::qtAppClass ui;
	void createActions();
    void createTrayIcon();

	QAction *encryptFolderAction;
    QAction *decryptFileAction;
    QAction *encryptFileAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif // QTAPP_H
