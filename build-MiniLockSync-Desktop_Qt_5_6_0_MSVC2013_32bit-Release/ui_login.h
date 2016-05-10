/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *eMailLineEdit;
    QLabel *label1;
    QPushButton *cancelButton;
    QLineEdit *passwdLineEdit;
    QLabel *label_2;
    QPushButton *loginButton;
    QLabel *label3;
    QLineEdit *yourIdLineEdit;
    QPushButton *startButton;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(400, 300);
        layoutWidget = new QWidget(login);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 30, 299, 158));
        gridLayout_3 = new QGridLayout(layoutWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        eMailLineEdit = new QLineEdit(layoutWidget);
        eMailLineEdit->setObjectName(QStringLiteral("eMailLineEdit"));

        gridLayout->addWidget(eMailLineEdit, 0, 1, 1, 1);

        label1 = new QLabel(layoutWidget);
        label1->setObjectName(QStringLiteral("label1"));

        gridLayout->addWidget(label1, 0, 0, 1, 1);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setAutoDefault(true);

        gridLayout->addWidget(cancelButton, 1, 2, 1, 1);

        passwdLineEdit = new QLineEdit(layoutWidget);
        passwdLineEdit->setObjectName(QStringLiteral("passwdLineEdit"));

        gridLayout->addWidget(passwdLineEdit, 1, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        loginButton = new QPushButton(layoutWidget);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setAutoDefault(true);

        gridLayout->addWidget(loginButton, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        label3 = new QLabel(layoutWidget);
        label3->setObjectName(QStringLiteral("label3"));
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        label3->setFont(font);

        gridLayout_3->addWidget(label3, 1, 0, 1, 1);

        yourIdLineEdit = new QLineEdit(layoutWidget);
        yourIdLineEdit->setObjectName(QStringLiteral("yourIdLineEdit"));

        gridLayout_3->addWidget(yourIdLineEdit, 2, 0, 1, 1);

        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setAutoDefault(true);

        gridLayout_3->addWidget(startButton, 3, 0, 1, 1);

        QWidget::setTabOrder(eMailLineEdit, passwdLineEdit);
        QWidget::setTabOrder(passwdLineEdit, loginButton);
        QWidget::setTabOrder(loginButton, startButton);
        QWidget::setTabOrder(startButton, cancelButton);
        QWidget::setTabOrder(cancelButton, yourIdLineEdit);

        retranslateUi(login);
        QObject::connect(cancelButton, SIGNAL(clicked()), login, SLOT(close()));
        QObject::connect(loginButton, SIGNAL(clicked()), login, SLOT(loginButton_click()));
        QObject::connect(startButton, SIGNAL(clicked()), login, SLOT(startButton_click()));

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QApplication::translate("login", "login", 0));
        label1->setText(QApplication::translate("login", "Benutzername:", 0));
        cancelButton->setText(QApplication::translate("login", "Abbrechen", 0));
        label_2->setText(QApplication::translate("login", "Passwort:", 0));
        loginButton->setText(QApplication::translate("login", "Login", 0));
        label3->setText(QApplication::translate("login", "Generierter Sicherheitsschl\303\274ssel:", 0));
        startButton->setText(QApplication::translate("login", "Start", 0));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
