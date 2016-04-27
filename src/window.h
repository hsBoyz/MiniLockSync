#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>

namespace Ui {
class Window;
}

class Window : public QDialog
{
    Q_OBJECT


public slots:



public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:

    void on_pushHome_clicked();

    void on_pushCloudService_clicked();

    void on_pushManageCloud_clicked();

    void on_pushCPULimitation_clicked();

    void on_pushChangePassword_clicked();



private:
    Ui::Window *ui;


};

#endif // WINDOW_H
