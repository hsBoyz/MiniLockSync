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
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
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
    QPushButton *pushCPULimitation;
    QPushButton *pushChangePassword;
    QGroupBox *groupBox_3;
    QStackedWidget *stackedWidget;
    QWidget *Home;
    QTextBrowser *textBrowser_5;
    QWidget *CloudService;
    QTextBrowser *textBrowser;
    QWidget *ManageCloud;
    QTextBrowser *textBrowser_2;
    QWidget *CPULimitation;
    QTextBrowser *textBrowser_3;
    QWidget *ChangePasword;
    QTextBrowser *textBrowser_4;

    void setupUi(QDialog *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QStringLiteral("Window"));
        Window->resize(800, 640);
        groupBox = new QGroupBox(Window);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(100, 70, 671, 551));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 50, 141, 171));
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

        pushCPULimitation = new QPushButton(groupBox_2);
        pushCPULimitation->setObjectName(QStringLiteral("pushCPULimitation"));

        verticalLayout_3->addWidget(pushCPULimitation);

        pushChangePassword = new QPushButton(groupBox_2);
        pushChangePassword->setObjectName(QStringLiteral("pushChangePassword"));

        verticalLayout_3->addWidget(pushChangePassword);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(150, 50, 471, 481));
        stackedWidget = new QStackedWidget(groupBox_3);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(20, 20, 441, 441));
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
        textBrowser_2 = new QTextBrowser(ManageCloud);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(120, 20, 171, 31));
        stackedWidget->addWidget(ManageCloud);
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

        retranslateUi(Window);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QDialog *Window)
    {
        Window->setWindowTitle(QApplication::translate("Window", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("Window", "GroupBox", 0));
        groupBox_2->setTitle(QApplication::translate("Window", "GroupBox", 0));
        pushHome->setText(QApplication::translate("Window", "Home", 0));
        pushCloudService->setText(QApplication::translate("Window", "Cloud Service", 0));
        pushManageCloud->setText(QApplication::translate("Window", "Manage Cloud Service", 0));
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
        textBrowser_2->setHtml(QApplication::translate("Window", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Manage Cloud Service</span></p></body></html>", 0));
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
