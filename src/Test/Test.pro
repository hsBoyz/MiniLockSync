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
    settingsmanager.cpp \
    handlefiles.cpp \
    steerer.cpp \
    watcher.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    filewindow.h \
    settingsmanager.h \
    handlefiles.h \
    steerer.h \
    watcher.h

FORMS    += mainwindow.ui \
    filewindow.ui \
    steerer.ui \
    steerer2.ui

RESOURCES += \
    icon.qrc
