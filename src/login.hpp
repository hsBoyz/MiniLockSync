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
    void saveLogin_click();
    void saveLogin();
    void loadLogin();
    //void autostart();
	
	void startButton_click();
	

public:
	Ui::login ui;
    static uCrypt::uCryptLib mainSession;
    static bool isInitialized;
<<<<<<< HEAD
    static QString user;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
=======

    private:

    // >>> Singleton impl
    //Steerer(QWidget *parent = 0);
    login(const login&);
    login &operator=(const login&);
    // <<<
>>>>>>> remotes/originHttps/Branch_gui_luca2
};
