#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QDialog>

namespace Ui {
class FileWindow;
}

class FileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FileWindow(QWidget *parent = 0);
    ~FileWindow();

private:
    Ui::FileWindow *ui;
};

#endif // FILEWINDOW_H
