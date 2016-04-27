#-------------------------------------------------
#
# Project created by QtCreator 2016-04-24T13:12:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MiniLockSync
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    steerer.cpp \
    settingsmanager.cpp \
    window.cpp

HEADERS  += mainwindow.h \
    steerer.h \
    settingsmanager.h \
    window.h

FORMS    += mainwindow.ui \
    steerer.ui \
    window.ui

RESOURCES += \
    resources.qrc
