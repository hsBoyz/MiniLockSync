#pragma once
#include <QWidget>
#include "ui_login.h"
#include <uCryptLib.h>


class login : public QWidget {
	Q_OBJECT

public:
	login(QWidget * parent = Q_NULLPTR);

    uCrypt::uCryptLib getMainSession();

	~login();

protected:
    void closeEvent(QCloseEvent *event);

	public slots:
	void loginButton_click();
    void cancelButton_click();
    void saveLogin_click();
    void saveLogin();
    void loadLogin();
	
	void startButton_click();
	

private:
	Ui::login ui;
    uCrypt::uCryptLib mainSession;
	bool isInitialized;
};
