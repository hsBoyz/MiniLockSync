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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_back;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_encrypt;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_deleteFile;
    QListView *listView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FileWindow)
    {
        if (FileWindow->objectName().isEmpty())
            FileWindow->setObjectName(QStringLiteral("FileWindow"));
        FileWindow->resize(821, 541);
        centralwidget = new QWidget(FileWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_back = new QPushButton(centralwidget);
        pushButton_back->setObjectName(QStringLiteral("pushButton_back"));

        horizontalLayout->addWidget(pushButton_back);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_encrypt = new QPushButton(centralwidget);
        pushButton_encrypt->setObjectName(QStringLiteral("pushButton_encrypt"));

        horizontalLayout->addWidget(pushButton_encrypt);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_deleteFile = new QPushButton(centralwidget);
        pushButton_deleteFile->setObjectName(QStringLiteral("pushButton_deleteFile"));

        horizontalLayout->addWidget(pushButton_deleteFile);


        verticalLayout->addLayout(horizontalLayout);

        listView = new QListView(centralwidget);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout->addWidget(listView);

        FileWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FileWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 821, 26));
        FileWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(FileWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        FileWindow->setStatusBar(statusbar);

        retranslateUi(FileWindow);

        QMetaObject::connectSlotsByName(FileWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FileWindow)
    {
        FileWindow->setWindowTitle(QApplication::translate("FileWindow", "MainWindow", 0));
        pushButton_back->setText(QApplication::translate("FileWindow", "Back", 0));
        pushButton_encrypt->setText(QApplication::translate("FileWindow", "Encrypt", 0));
        pushButton_deleteFile->setText(QApplication::translate("FileWindow", "Delete", 0));
    } // retranslateUi

};

namespace Ui {
    class FileWindow: public Ui_FileWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEWINDOW_H
