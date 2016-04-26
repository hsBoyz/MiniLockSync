#ifndef STEERER_H
#define STEERER_H

#include "stackedwindow.h"

#include <QWidget>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QAction>

namespace Ui {
class Steerer;
}

class Steerer : public QWidget
{
    Q_OBJECT

public:
    explicit Steerer(QWidget *parent = 0);
    ~Steerer();

    void start();


private slots:
    void showSettings();
    void openFileWindow();


private:
    Ui::Steerer *ui;


    void createActions();
    void createTrayIcon();
    QAction *settingsAction;
    QAction *quitAction;
    QAction *openAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    StackedWindow *stackedwin;

};

#endif // STEERER_H
