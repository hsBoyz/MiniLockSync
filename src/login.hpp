#pragma once
#include <QWidget>
#include "ui_login.h"
#include <uCryptLib.h>



class login : public QWidget {
	Q_OBJECT

public:
    // >>> Singleton impl
    static login &GetInstance() {
        static login Instanz;
        return Instanz;
    }
    // <<<
	login(QWidget * parent = Q_NULLPTR);

    uCrypt::uCryptLib getMainSession();
    bool getIsInitialized();

	~login();




protected:
    void closeEvent(QCloseEvent *event);

	public slots:
	void loginButton_click();
    void cancelButton_click();
    void saveLogin_click(int check);
    void saveLogin();
    void loadLogin(QString user);
    void loginDataConfirmed();
    //void autostart();
	
	void startButton_click();
    void enableLoginButton();
    void setConPasswd();
	

public:
	Ui::login ui;
    static uCrypt::uCryptLib mainSession;
    static bool isInitialized;
    static QString user;
private slots:
    void checkUserName();
    bool checkPassword();

    private:

    // >>> Singleton impl
    //Steerer(QWidget *parent = 0);
    login(const login&);
    login &operator=(const login&);
    // <<<
    bool userExists = false;
};
