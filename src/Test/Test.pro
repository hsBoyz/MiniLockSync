#-------------------------------------------------
#
# Project created by QtCreator 2016-04-11T12:40:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filewindow.cpp \
    settingsmanager.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    filewindow.h \
    settingsmanager.h

FORMS    += mainwindow.ui \
    filewindow.ui

RESOURCES += \
    icon.qrc
