#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QMainWindow>

namespace Ui {
class FileWindow;
}

class FileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileWindow(QWidget *parent = 0);
    ~FileWindow();

private:
    Ui::FileWindow *ui;
};

#endif // FILEWINDOW_H
