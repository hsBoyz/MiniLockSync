#ifndef STEERER_H
#define STEERER_H

#include "timer.h"
#include <QTimer>
#include <QThread>
#include <QWidget>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QAction>
#include <handlefiles.h>

namespace Ui {
class Steerer;
}

class Steerer : public QWidget
{
    Q_OBJECT

public:

    // >>> Singleton impl
    static Steerer &GetInstance() {
        static Steerer Instanz;
        return Instanz;
    }
    // <<<
    explicit Steerer(QWidget *parent = 0);
    ~Steerer();

    void start();


private slots:
    void showSettings();
    void openFileWindow();
    void logout();
    void trayLeftClick(QSystemTrayIcon::ActivationReason reason);


private:
    // >>> Singleton impl
    //Steerer(QWidget *parent = 0);
    Steerer(const Steerer&);
    Steerer &operator=(const Steerer&);
    // <<<
    Ui::Steerer *ui;




    void createActions();
    void createTrayIcon();
    QAction *settingsAction;
    QAction *quitAction;
    QAction *openAction;
    QAction *logoutAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    bool checkSettings();
    void startAutoSync();



};

#endif // STEERER_H
