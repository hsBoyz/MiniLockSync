/********************************************************************************
** Form generated from reading UI file 'steerer.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STEERER_H
#define UI_STEERER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Steerer
{
public:

    void setupUi(QWidget *Steerer)
    {
        if (Steerer->objectName().isEmpty())
            Steerer->setObjectName(QStringLiteral("Steerer"));
        Steerer->resize(400, 300);

        retranslateUi(Steerer);

        QMetaObject::connectSlotsByName(Steerer);
    } // setupUi

    void retranslateUi(QWidget *Steerer)
    {
        Steerer->setWindowTitle(QApplication::translate("Steerer", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Steerer: public Ui_Steerer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STEERER_H
