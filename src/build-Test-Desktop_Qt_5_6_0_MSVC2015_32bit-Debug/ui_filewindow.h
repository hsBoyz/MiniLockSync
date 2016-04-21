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
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileWindow
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QListView *listView_2;
    QListView *listView_saftyCopy;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *label_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *removeFile;

    void setupUi(QDialog *FileWindow)
    {
        if (FileWindow->objectName().isEmpty())
            FileWindow->setObjectName(QStringLiteral("FileWindow"));
        FileWindow->resize(1140, 700);
        layoutWidget = new QWidget(FileWindow);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 530, 761, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setEnabled(true);

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);

        layoutWidget1 = new QWidget(FileWindow);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(60, 150, 931, 351));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        listView_2 = new QListView(layoutWidget1);
        listView_2->setObjectName(QStringLiteral("listView_2"));
        listView_2->setAcceptDrops(false);

        horizontalLayout_2->addWidget(listView_2);

        listView_saftyCopy = new QListView(layoutWidget1);
        listView_saftyCopy->setObjectName(QStringLiteral("listView_saftyCopy"));

        horizontalLayout_2->addWidget(listView_saftyCopy);

        layoutWidget2 = new QWidget(FileWindow);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(60, 50, 931, 61));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

        horizontalLayout_3->addWidget(label);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setWordWrap(true);

        horizontalLayout_3->addWidget(label_3);

        pushButton_5 = new QPushButton(FileWindow);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(60, 130, 75, 23));
        pushButton_6 = new QPushButton(FileWindow);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(140, 130, 91, 23));
        removeFile = new QPushButton(FileWindow);
        removeFile->setObjectName(QStringLiteral("removeFile"));
        removeFile->setGeometry(QRect(60, 590, 131, 23));

        retranslateUi(FileWindow);

        QMetaObject::connectSlotsByName(FileWindow);
    } // setupUi

    void retranslateUi(QDialog *FileWindow)
    {
        FileWindow->setWindowTitle(QApplication::translate("FileWindow", "Dialog", 0));
        pushButton->setText(QApplication::translate("FileWindow", "Save", 0));
        pushButton_2->setText(QApplication::translate("FileWindow", "Load", 0));
        pushButton_3->setText(QApplication::translate("FileWindow", "RemoveAllKeys", 0));
        pushButton_4->setText(QApplication::translate("FileWindow", "PrintGroupsToConsole", 0));
        label->setText(QString());
        label_3->setText(QApplication::translate("FileWindow", "Sicherungskopien", 0));
        pushButton_5->setText(QApplication::translate("FileWindow", "Back", 0));
        pushButton_6->setText(QApplication::translate("FileWindow", "Change view", 0));
        removeFile->setText(QApplication::translate("FileWindow", "removeSelectedFile", 0));
    } // retranslateUi

};

namespace Ui {
    class FileWindow: public Ui_FileWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEWINDOW_H
