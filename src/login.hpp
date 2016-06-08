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
<<<<<<< HEAD
=======
    void setConPasswd();
>>>>>>> GUI_Luca
	

public:
	Ui::login ui;
    static uCrypt::uCryptLib mainSession;
    static bool isInitialized;
    static QString user;
private slots:
<<<<<<< HEAD
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
=======
>>>>>>> GUI_Luca
    void checkUserName();
    bool checkPassword();

    private:

    // >>> Singleton impl
    login(QWidget * parent = Q_NULLPTR);
    login(const login&);
    login &operator=(const login&);
    // <<<
<<<<<<< HEAD
    bool userExists;
=======
    bool userExists = false;
>>>>>>> GUI_Luca
};
