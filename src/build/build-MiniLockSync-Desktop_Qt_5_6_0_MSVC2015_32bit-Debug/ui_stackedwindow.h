/********************************************************************************
** Form generated from reading UI file 'stackedwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STACKEDWINDOW_H
#define UI_STACKEDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StackedWindow
{
public:
    QWidget *Main;
    QTextBrowser *textBrowser;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushManage;
    QPushButton *pushSettings;
    QWidget *Manage;
    QTextBrowser *textBrowser_2;
    QPushButton *pushZurueckManage;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_2;
    QPushButton *pushDropbox;
    QPushButton *pushICloud;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QPushButton *pushButton_9;
    QWidget *Settings;
    QPushButton *pushZurueckSettings;
    QLabel *label;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget_2;
    QWidget *welcome;
    QLabel *label_2;
    QWidget *AddCloud;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushAddCloud;
    QPushButton *pushCPULimit;
    QPushButton *pushChangePW;
    QGroupBox *groupBox_4;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QTreeView *treeView_fileBrowser;
    QPushButton *pushButton_addDir;
    QTableWidget *tableWidget;
    QPushButton *pushButton_10;
    QWidget *CPU;
    QLabel *label_3;
    QWidget *ChangePW;
    QLabel *label_4;
    QWidget *AddCloud2;
    QWidget *Dropbox;
    QPushButton *pushZurueckDropbox;
    QTextBrowser *textBrowser_4;
    QTextBrowser *textBrowser_7;
    QWidget *ICloud;
    QPushButton *pushZurueckICloud;
    QTextBrowser *textBrowser_5;
    QTextBrowser *textBrowser_6;

    void setupUi(QStackedWidget *StackedWindow)
    {
        if (StackedWindow->objectName().isEmpty())
            StackedWindow->setObjectName(QStringLiteral("StackedWindow"));
        StackedWindow->resize(1140, 680);
        Main = new QWidget();
        Main->setObjectName(QStringLiteral("Main"));
        textBrowser = new QTextBrowser(Main);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(90, 40, 281, 51));
        verticalLayoutWidget_2 = new QWidget(Main);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(50, 160, 160, 81));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushManage = new QPushButton(verticalLayoutWidget_2);
        pushManage->setObjectName(QStringLiteral("pushManage"));

        verticalLayout_2->addWidget(pushManage);

        pushSettings = new QPushButton(verticalLayoutWidget_2);
        pushSettings->setObjectName(QStringLiteral("pushSettings"));

        verticalLayout_2->addWidget(pushSettings);

        StackedWindow->addWidget(Main);
        Manage = new QWidget();
        Manage->setObjectName(QStringLiteral("Manage"));
        textBrowser_2 = new QTextBrowser(Manage);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(90, 40, 281, 51));
        pushZurueckManage = new QPushButton(Manage);
        pushZurueckManage->setObjectName(QStringLiteral("pushZurueckManage"));
        pushZurueckManage->setGeometry(QRect(10, 40, 61, 51));
        groupBox = new QGroupBox(Manage);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(130, 130, 371, 331));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 30, 301, 345));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_6 = new QPushButton(gridLayoutWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 6, 0, 1, 1);

        pushButton_7 = new QPushButton(gridLayoutWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout->addWidget(pushButton_7, 7, 0, 1, 1);

        pushButton_8 = new QPushButton(gridLayoutWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout->addWidget(pushButton_8, 8, 0, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 2, 0, 1, 1);

        pushDropbox = new QPushButton(gridLayoutWidget);
        pushDropbox->setObjectName(QStringLiteral("pushDropbox"));

        gridLayout->addWidget(pushDropbox, 0, 0, 1, 1);

        pushICloud = new QPushButton(gridLayoutWidget);
        pushICloud->setObjectName(QStringLiteral("pushICloud"));

        gridLayout->addWidget(pushICloud, 1, 0, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 3, 0, 1, 1);

        pushButton_5 = new QPushButton(gridLayoutWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 5, 0, 1, 1);

        pushButton_4 = new QPushButton(gridLayoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 4, 0, 1, 1);

        pushButton_9 = new QPushButton(gridLayoutWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        gridLayout->addWidget(pushButton_9, 9, 0, 1, 1);

        StackedWindow->addWidget(Manage);
        Settings = new QWidget();
        Settings->setObjectName(QStringLiteral("Settings"));
        pushZurueckSettings = new QPushButton(Settings);
        pushZurueckSettings->setObjectName(QStringLiteral("pushZurueckSettings"));
        pushZurueckSettings->setGeometry(QRect(20, 30, 61, 31));
        label = new QLabel(Settings);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(210, 30, 151, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(true);
        font.setWeight(50);
        label->setFont(font);
        groupBox_2 = new QGroupBox(Settings);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 70, 781, 521));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        stackedWidget_2 = new QStackedWidget(groupBox_2);
        stackedWidget_2->setObjectName(QStringLiteral("stackedWidget_2"));
        welcome = new QWidget();
        welcome->setObjectName(QStringLiteral("welcome"));
        label_2 = new QLabel(welcome);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 80, 301, 101));
        stackedWidget_2->addWidget(welcome);
        AddCloud = new QWidget();
        AddCloud->setObjectName(QStringLiteral("AddCloud"));
        groupBox_3 = new QGroupBox(AddCloud);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 70, 191, 301));
        layoutWidget = new QWidget(groupBox_3);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 116, 171));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushAddCloud = new QPushButton(layoutWidget);
        pushAddCloud->setObjectName(QStringLiteral("pushAddCloud"));

        verticalLayout->addWidget(pushAddCloud);

        pushCPULimit = new QPushButton(layoutWidget);
        pushCPULimit->setObjectName(QStringLiteral("pushCPULimit"));

        verticalLayout->addWidget(pushCPULimit);

        pushChangePW = new QPushButton(layoutWidget);
        pushChangePW->setObjectName(QStringLiteral("pushChangePW"));

        verticalLayout->addWidget(pushChangePW);

        groupBox_4 = new QGroupBox(AddCloud);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(230, 10, 511, 491));
        verticalLayoutWidget = new QWidget(groupBox_4);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 30, 258, 450));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        treeView_fileBrowser = new QTreeView(verticalLayoutWidget);
        treeView_fileBrowser->setObjectName(QStringLiteral("treeView_fileBrowser"));

        verticalLayout_3->addWidget(treeView_fileBrowser);

        pushButton_addDir = new QPushButton(verticalLayoutWidget);
        pushButton_addDir->setObjectName(QStringLiteral("pushButton_addDir"));

        verticalLayout_3->addWidget(pushButton_addDir);

        tableWidget = new QTableWidget(verticalLayoutWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout_3->addWidget(tableWidget);

        pushButton_10 = new QPushButton(verticalLayoutWidget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        verticalLayout_3->addWidget(pushButton_10);

        stackedWidget_2->addWidget(AddCloud);
        CPU = new QWidget();
        CPU->setObjectName(QStringLiteral("CPU"));
        label_3 = new QLabel(CPU);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 90, 161, 71));
        stackedWidget_2->addWidget(CPU);
        ChangePW = new QWidget();
        ChangePW->setObjectName(QStringLiteral("ChangePW"));
        label_4 = new QLabel(ChangePW);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(110, 90, 171, 101));
        stackedWidget_2->addWidget(ChangePW);

        horizontalLayout->addWidget(stackedWidget_2);

        StackedWindow->addWidget(Settings);
        AddCloud2 = new QWidget();
        AddCloud2->setObjectName(QStringLiteral("AddCloud2"));
        StackedWindow->addWidget(AddCloud2);
        Dropbox = new QWidget();
        Dropbox->setObjectName(QStringLiteral("Dropbox"));
        pushZurueckDropbox = new QPushButton(Dropbox);
        pushZurueckDropbox->setObjectName(QStringLiteral("pushZurueckDropbox"));
        pushZurueckDropbox->setGeometry(QRect(10, 40, 61, 51));
        textBrowser_4 = new QTextBrowser(Dropbox);
        textBrowser_4->setObjectName(QStringLiteral("textBrowser_4"));
        textBrowser_4->setGeometry(QRect(90, 40, 281, 51));
        textBrowser_7 = new QTextBrowser(Dropbox);
        textBrowser_7->setObjectName(QStringLiteral("textBrowser_7"));
        textBrowser_7->setGeometry(QRect(140, 110, 181, 41));
        StackedWindow->addWidget(Dropbox);
        ICloud = new QWidget();
        ICloud->setObjectName(QStringLiteral("ICloud"));
        pushZurueckICloud = new QPushButton(ICloud);
        pushZurueckICloud->setObjectName(QStringLiteral("pushZurueckICloud"));
        pushZurueckICloud->setGeometry(QRect(10, 40, 61, 51));
        textBrowser_5 = new QTextBrowser(ICloud);
        textBrowser_5->setObjectName(QStringLiteral("textBrowser_5"));
        textBrowser_5->setGeometry(QRect(90, 40, 281, 51));
        textBrowser_6 = new QTextBrowser(ICloud);
        textBrowser_6->setObjectName(QStringLiteral("textBrowser_6"));
        textBrowser_6->setGeometry(QRect(140, 110, 181, 41));
        StackedWindow->addWidget(ICloud);

        retranslateUi(StackedWindow);

        StackedWindow->setCurrentIndex(2);
        stackedWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(StackedWindow);
    } // setupUi

    void retranslateUi(QStackedWidget *StackedWindow)
    {
        StackedWindow->setWindowTitle(QApplication::translate("StackedWindow", "StackedWidget", 0));
        textBrowser->setHtml(QApplication::translate("StackedWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" dir='rtl' style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt; font-weight:600; font-style:italic;\">MiniLockSync</span></p></body></html>", 0));
        pushManage->setText(QApplication::translate("StackedWindow", "Manage Cloud Service", 0));
        pushSettings->setText(QApplication::translate("StackedWindow", "Settings", 0));
        textBrowser_2->setHtml(QApplication::translate("StackedWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" dir='rtl' style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt; font-weight:600; font-style:italic;\">MiniLockSync</span></p></body></html>", 0));
        pushZurueckManage->setText(QApplication::translate("StackedWindow", "zur\303\274ck", 0));
        groupBox->setTitle(QApplication::translate("StackedWindow", "Cloud Services", 0));
        pushButton_6->setText(QApplication::translate("StackedWindow", "PushButton", 0));
        pushButton_7->setText(QApplication::translate("StackedWindow", "PushButton", 0));
        pushButton_8->setText(QApplication::translate("StackedWindow", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("StackedWindow", "PushButton", 0));
        pushDropbox->setText(QApplication::translate("StackedWindow", "Dropbox", 0));
        pushICloud->setText(QApplication::translate("StackedWindow", "ICloud", 0));
        pushButton_3->setText(QApplication::translate("StackedWindow", "PushButton", 0));
        pushButton_5->setText(QApplication::translate("StackedWindow", "PushButton", 0));
        pushButton_4->setText(QApplication::translate("StackedWindow", "PushButton", 0));
        pushButton_9->setText(QApplication::translate("StackedWindow", "PushButton", 0));
        pushZurueckSettings->setText(QApplication::translate("StackedWindow", "back", 0));
        label->setText(QApplication::translate("StackedWindow", "Version 1.0.2", 0));
        groupBox_2->setTitle(QApplication::translate("StackedWindow", "Settings", 0));
        label_2->setText(QApplication::translate("StackedWindow", "Hier k\303\266nnen sie Einstellungen vornehmen", 0));
        groupBox_3->setTitle(QApplication::translate("StackedWindow", "GroupBox", 0));
        pushAddCloud->setText(QApplication::translate("StackedWindow", "Manage Cloud Service", 0));
        pushCPULimit->setText(QApplication::translate("StackedWindow", "CPU-Limitation", 0));
        pushChangePW->setText(QApplication::translate("StackedWindow", "Change Password", 0));
        groupBox_4->setTitle(QApplication::translate("StackedWindow", "GroupBox", 0));
        pushButton_addDir->setText(QApplication::translate("StackedWindow", "Add", 0));
        pushButton_10->setText(QApplication::translate("StackedWindow", "Delete", 0));
        label_3->setText(QApplication::translate("StackedWindow", "CPU-Limitation -> ToDO", 0));
        label_4->setText(QApplication::translate("StackedWindow", "Passwort \303\244ndern! -> ToDO", 0));
        pushZurueckDropbox->setText(QApplication::translate("StackedWindow", "zur\303\274ck", 0));
        textBrowser_4->setHtml(QApplication::translate("StackedWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" dir='rtl' style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt; font-weight:600; font-style:italic;\">MiniLockSync</span></p></body></html>", 0));
        textBrowser_7->setHtml(QApplication::translate("StackedWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Dropbox</span></p></body></html>", 0));
        pushZurueckICloud->setText(QApplication::translate("StackedWindow", "zur\303\274ck", 0));
        textBrowser_5->setHtml(QApplication::translate("StackedWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" dir='rtl' style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt; font-weight:600; font-style:italic;\">MiniLockSync</span></p></body></html>", 0));
        textBrowser_6->setHtml(QApplication::translate("StackedWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">ICloud</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class StackedWindow: public Ui_StackedWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STACKEDWINDOW_H
