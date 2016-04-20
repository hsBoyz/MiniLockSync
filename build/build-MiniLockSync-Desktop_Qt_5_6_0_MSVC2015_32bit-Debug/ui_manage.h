/********************************************************************************
** Form generated from reading UI file 'manage.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGE_H
#define UI_MANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Manage
{
public:
    QPushButton *pushDropBox;

    void setupUi(QDialog *Manage)
    {
        if (Manage->objectName().isEmpty())
            Manage->setObjectName(QStringLiteral("Manage"));
        Manage->resize(494, 369);
        pushDropBox = new QPushButton(Manage);
        pushDropBox->setObjectName(QStringLiteral("pushDropBox"));
        pushDropBox->setGeometry(QRect(30, 40, 121, 51));

        retranslateUi(Manage);

        QMetaObject::connectSlotsByName(Manage);
    } // setupUi

    void retranslateUi(QDialog *Manage)
    {
        Manage->setWindowTitle(QApplication::translate("Manage", "Dialog", 0));
        pushDropBox->setText(QApplication::translate("Manage", "Dropbox", 0));
    } // retranslateUi

};

namespace Ui {
    class Manage: public Ui_Manage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGE_H
