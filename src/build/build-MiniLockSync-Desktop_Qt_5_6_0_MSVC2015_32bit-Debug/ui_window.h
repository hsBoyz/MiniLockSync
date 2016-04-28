/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushHome;
    QPushButton *pushCloudService;
    QPushButton *pushManageCloud;
    QPushButton *pushManageSaveDir;
    QPushButton *pushCPULimitation;
    QPushButton *pushChangePassword;
    QGroupBox *groupBox_3;
    QStackedWidget *stackedWidget;
    QWidget *Home;
    QTextBrowser *textBrowser_5;
    QWidget *CloudService;
    QTextBrowser *textBrowser;
    QWidget *ManageCloud;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView_fileBrowser;
    QPushButton *pushButton_addDir;
    QTableWidget *tableWidget;
    QPushButton *pushButton_deleteDir;
    QPushButton *pushButton_confirm;
    QWidget *ManageWorkSaveDir;
    QVBoxLayout *verticalLayout_2;
    QTreeView *treeView_dirBrowser;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_addWorkDir;
    QPushButton *pushButton_addSaveDir;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget_dir;
    QTableWidget *tableWidget_save;
    QPushButton *pushButton_deleteDir_2;
    QWidget *CPULimitation;
    QTextBrowser *textBrowser_3;
    QWidget *ChangePasword;
    QTextBrowser *textBrowser_4;

    void setupUi(QMainWindow *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QStringLiteral("Window"));
        Window->resize(1127, 691);
        Window->setContextMenuPolicy(Qt::DefaultContextMenu);
        groupBox = new QGroupBox(Window);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setEnabled(true);
        groupBox_2->setGeometry(QRect(0, 50, 141, 311));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushHome = new QPushButton(groupBox_2);
        pushHome->setObjectName(QStringLiteral("pushHome"));

        verticalLayout_3->addWidget(pushHome);

        pushCloudService = new QPushButton(groupBox_2);
        pushCloudService->setObjectName(QStringLiteral("pushCloudService"));

        verticalLayout_3->addWidget(pushCloudService);

        pushManageCloud = new QPushButton(groupBox_2);
        pushManageCloud->setObjectName(QStringLiteral("pushManageCloud"));

        verticalLayout_3->addWidget(pushManageCloud);

        pushManageSaveDir = new QPushButton(groupBox_2);
        pushManageSaveDir->setObjectName(QStringLiteral("pushManageSaveDir"));

        verticalLayout_3->addWidget(pushManageSaveDir);

        pushCPULimitation = new QPushButton(groupBox_2);
        pushCPULimitation->setObjectName(QStringLiteral("pushCPULimitation"));

        verticalLayout_3->addWidget(pushCPULimitation);

        pushChangePassword = new QPushButton(groupBox_2);
        pushChangePassword->setObjectName(QStringLiteral("pushChangePassword"));

        verticalLayout_3->addWidget(pushChangePassword);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(150, 50, 791, 551));
        stackedWidget = new QStackedWidget(groupBox_3);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(20, 20, 761, 531));
        Home = new QWidget();
        Home->setObjectName(QStringLiteral("Home"));
        textBrowser_5 = new QTextBrowser(Home);
        textBrowser_5->setObjectName(QStringLiteral("textBrowser_5"));
        textBrowser_5->setGeometry(QRect(60, 40, 291, 261));
        stackedWidget->addWidget(Home);
        CloudService = new QWidget();
        CloudService->setObjectName(QStringLiteral("CloudService"));
        textBrowser = new QTextBrowser(CloudService);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(150, 20, 111, 31));
        stackedWidget->addWidget(CloudService);
        ManageCloud = new QWidget();
        ManageCloud->setObjectName(QStringLiteral("ManageCloud"));
        verticalLayout = new QVBoxLayout(ManageCloud);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeView_fileBrowser = new QTreeView(ManageCloud);
        treeView_fileBrowser->setObjectName(QStringLiteral("treeView_fileBrowser"));

        verticalLayout->addWidget(treeView_fileBrowser);

        pushButton_addDir = new QPushButton(ManageCloud);
        pushButton_addDir->setObjectName(QStringLiteral("pushButton_addDir"));

        verticalLayout->addWidget(pushButton_addDir);

        tableWidget = new QTableWidget(ManageCloud);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        pushButton_deleteDir = new QPushButton(ManageCloud);
        pushButton_deleteDir->setObjectName(QStringLiteral("pushButton_deleteDir"));

        verticalLayout->addWidget(pushButton_deleteDir);

        pushButton_confirm = new QPushButton(ManageCloud);
        pushButton_confirm->setObjectName(QStringLiteral("pushButton_confirm"));

        verticalLayout->addWidget(pushButton_confirm);

        stackedWidget->addWidget(ManageCloud);
        ManageWorkSaveDir = new QWidget();
        ManageWorkSaveDir->setObjectName(QStringLiteral("ManageWorkSaveDir"));
        verticalLayout_2 = new QVBoxLayout(ManageWorkSaveDir);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        treeView_dirBrowser = new QTreeView(ManageWorkSaveDir);
        treeView_dirBrowser->setObjectName(QStringLiteral("treeView_dirBrowser"));

        verticalLayout_2->addWidget(treeView_dirBrowser);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_addWorkDir = new QPushButton(ManageWorkSaveDir);
        pushButton_addWorkDir->setObjectName(QStringLiteral("pushButton_addWorkDir"));

        horizontalLayout_2->addWidget(pushButton_addWorkDir);

        pushButton_addSaveDir = new QPushButton(ManageWorkSaveDir);
        pushButton_addSaveDir->setObjectName(QStringLiteral("pushButton_addSaveDir"));

        horizontalLayout_2->addWidget(pushButton_addSaveDir);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableWidget_dir = new QTableWidget(ManageWorkSaveDir);
        tableWidget_dir->setObjectName(QStringLiteral("tableWidget_dir"));

        horizontalLayout->addWidget(tableWidget_dir);

        tableWidget_save = new QTableWidget(ManageWorkSaveDir);
        tableWidget_save->setObjectName(QStringLiteral("tableWidget_save"));

        horizontalLayout->addWidget(tableWidget_save);


        verticalLayout_2->addLayout(horizontalLayout);

        pushButton_deleteDir_2 = new QPushButton(ManageWorkSaveDir);
        pushButton_deleteDir_2->setObjectName(QStringLiteral("pushButton_deleteDir_2"));

        verticalLayout_2->addWidget(pushButton_deleteDir_2);

        stackedWidget->addWidget(ManageWorkSaveDir);
        CPULimitation = new QWidget();
        CPULimitation->setObjectName(QStringLiteral("CPULimitation"));
        textBrowser_3 = new QTextBrowser(CPULimitation);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(150, 20, 121, 31));
        stackedWidget->addWidget(CPULimitation);
        ChangePasword = new QWidget();
        ChangePasword->setObjectName(QStringLiteral("ChangePasword"));
        textBrowser_4 = new QTextBrowser(ChangePasword);
        textBrowser_4->setObjectName(QStringLiteral("textBrowser_4"));
        textBrowser_4->setGeometry(QRect(140, 20, 141, 31));
        stackedWidget->addWidget(ChangePasword);
        Window->setCentralWidget(groupBox);

        retranslateUi(Window);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QMainWindow *Window)
    {
        Window->setWindowTitle(QApplication::translate("Window", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("Window", "GroupBox", 0));
        groupBox_2->setTitle(QApplication::translate("Window", "GroupBox", 0));
        pushHome->setText(QApplication::translate("Window", "Home", 0));
        pushCloudService->setText(QApplication::translate("Window", "Cloud Service", 0));
        pushManageCloud->setText(QApplication::translate("Window", "Manage Cloud Service", 0));
        pushManageSaveDir->setText(QApplication::translate("Window", "Manage Save/Work Dir", 0));
        pushCPULimitation->setText(QApplication::translate("Window", "CPU-Limitation", 0));
        pushChangePassword->setText(QApplication::translate("Window", "Change Password", 0));
        groupBox_3->setTitle(QApplication::translate("Window", "GroupBox", 0));
        textBrowser_5->setHtml(QApplication::translate("Window", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Willkommen blabla, ...</span></p></body></html>", 0));
        textBrowser->setHtml(QApplication::translate("Window", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Cloud Service</span></p></body></html>", 0));
        pushButton_addDir->setText(QApplication::translate("Window", "Add", 0));
        pushButton_deleteDir->setText(QApplication::translate("Window", "Delete", 0));
        pushButton_confirm->setText(QApplication::translate("Window", "Confirm", 0));
        pushButton_addWorkDir->setText(QApplication::translate("Window", "Add work directory", 0));
        pushButton_addSaveDir->setText(QApplication::translate("Window", "Add save directory", 0));
        pushButton_deleteDir_2->setText(QApplication::translate("Window", "Delete", 0));
        textBrowser_3->setHtml(QApplication::translate("Window", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">CPU-Limitation</span></p></body></html>", 0));
        textBrowser_4->setHtml(QApplication::translate("Window", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Change Password</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
