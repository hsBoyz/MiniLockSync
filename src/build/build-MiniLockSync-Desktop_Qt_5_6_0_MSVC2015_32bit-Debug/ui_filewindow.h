/********************************************************************************
** Form generated from reading UI file 'filewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEWINDOW_H
#define UI_FILEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileWindow
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FileWindow)
    {
        if (FileWindow->objectName().isEmpty())
            FileWindow->setObjectName(QStringLiteral("FileWindow"));
        FileWindow->resize(800, 600);
        menubar = new QMenuBar(FileWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        FileWindow->setMenuBar(menubar);
        centralwidget = new QWidget(FileWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        FileWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(FileWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        FileWindow->setStatusBar(statusbar);

        retranslateUi(FileWindow);

        QMetaObject::connectSlotsByName(FileWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FileWindow)
    {
        FileWindow->setWindowTitle(QApplication::translate("FileWindow", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class FileWindow: public Ui_FileWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEWINDOW_H
