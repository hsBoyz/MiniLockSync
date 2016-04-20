/********************************************************************************
** Form generated from reading UI file 'qtapp.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTAPP_H
#define UI_QTAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_qtAppClass
{
public:
    QLineEdit *eMailLineEdit;
    QLineEdit *passwdLineEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QPushButton *genPasswdButton;
    QLineEdit *yourIdLineEdit;
    QLabel *label_4;
    QLineEdit *recipientIdLineEdit;
    QPushButton *addButton;
    QComboBox *comboBox;
    QLabel *label_5;
    QPushButton *startButton;
    QFrame *line_5;
    QFrame *line_6;
    QFrame *line_7;
    QFrame *line_8;
    QPushButton *loginButton;

    void setupUi(QDialog *qtAppClass)
    {
        if (qtAppClass->objectName().isEmpty())
            qtAppClass->setObjectName(QStringLiteral("qtAppClass"));
        qtAppClass->resize(826, 479);
        eMailLineEdit = new QLineEdit(qtAppClass);
        eMailLineEdit->setObjectName(QStringLiteral("eMailLineEdit"));
        eMailLineEdit->setGeometry(QRect(80, 20, 381, 21));
        passwdLineEdit = new QLineEdit(qtAppClass);
        passwdLineEdit->setObjectName(QStringLiteral("passwdLineEdit"));
        passwdLineEdit->setGeometry(QRect(80, 60, 381, 20));
        label = new QLabel(qtAppClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 51, 21));
        label_2 = new QLabel(qtAppClass);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 60, 51, 20));
        label_3 = new QLabel(qtAppClass);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 110, 51, 21));
        line = new QFrame(qtAppClass);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 80, 541, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(qtAppClass);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 0, 541, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(qtAppClass);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(-10, 10, 41, 81));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(qtAppClass);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(540, 10, 21, 81));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        genPasswdButton = new QPushButton(qtAppClass);
        genPasswdButton->setObjectName(QStringLiteral("genPasswdButton"));
        genPasswdButton->setGeometry(QRect(470, 20, 71, 31));
        yourIdLineEdit = new QLineEdit(qtAppClass);
        yourIdLineEdit->setObjectName(QStringLiteral("yourIdLineEdit"));
        yourIdLineEdit->setGeometry(QRect(80, 110, 381, 20));
        yourIdLineEdit->setReadOnly(true);
        label_4 = new QLabel(qtAppClass);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 140, 51, 21));
        recipientIdLineEdit = new QLineEdit(qtAppClass);
        recipientIdLineEdit->setObjectName(QStringLiteral("recipientIdLineEdit"));
        recipientIdLineEdit->setGeometry(QRect(80, 140, 381, 20));
        addButton = new QPushButton(qtAppClass);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setGeometry(QRect(470, 140, 71, 23));
        comboBox = new QComboBox(qtAppClass);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(80, 170, 381, 22));
        label_5 = new QLabel(qtAppClass);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 170, 51, 21));
        startButton = new QPushButton(qtAppClass);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(470, 170, 71, 23));
        line_5 = new QFrame(qtAppClass);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(10, 190, 541, 20));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(qtAppClass);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(10, 90, 541, 20));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(qtAppClass);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(-10, 100, 41, 101));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);
        line_8 = new QFrame(qtAppClass);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setGeometry(QRect(530, 100, 41, 101));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);
        loginButton = new QPushButton(qtAppClass);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(470, 60, 71, 23));

        retranslateUi(qtAppClass);
        QObject::connect(loginButton, SIGNAL(clicked()), qtAppClass, SLOT(loginButton_click()));
        QObject::connect(genPasswdButton, SIGNAL(clicked()), qtAppClass, SLOT(genPasswdButton_click()));
        QObject::connect(addButton, SIGNAL(clicked()), qtAppClass, SLOT(addButton_click()));
        QObject::connect(startButton, SIGNAL(clicked()), qtAppClass, SLOT(startButton_click()));

        QMetaObject::connectSlotsByName(qtAppClass);
    } // setupUi

    void retranslateUi(QDialog *qtAppClass)
    {
        qtAppClass->setWindowTitle(QApplication::translate("qtAppClass", "qtApp", 0));
        label->setText(QApplication::translate("qtAppClass", "E-Mail:", 0));
        label_2->setText(QApplication::translate("qtAppClass", "Password:", 0));
        label_3->setText(QApplication::translate("qtAppClass", "Your ID:", 0));
        genPasswdButton->setText(QApplication::translate("qtAppClass", "Generate\n"
"Password", 0));
        label_4->setText(QApplication::translate("qtAppClass", "Recipient:", 0));
        addButton->setText(QApplication::translate("qtAppClass", "Add", 0));
        label_5->setText(QApplication::translate("qtAppClass", "Recipients:", 0));
        startButton->setText(QApplication::translate("qtAppClass", "Start", 0));
        loginButton->setText(QApplication::translate("qtAppClass", "Login", 0));
    } // retranslateUi

};

namespace Ui {
    class qtAppClass: public Ui_qtAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTAPP_H
