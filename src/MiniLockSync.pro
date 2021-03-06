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
    window.cpp \
    handlefiles.cpp \
    filewindow.cpp \
    login.cpp \
    worker.cpp \
    timer.cpp

HEADERS  += mainwindow.h \
    steerer.h \
    settingsmanager.h \
    window.h \
    handlefiles.h \
    filewindow.h \
    login.hpp \
    worker.h \
    timer.h

FORMS    += mainwindow.ui \
    steerer.ui \
    window.ui \
    filewindow.ui \
    login.ui

RESOURCES += \
    resources.qrc


TRANSLATIONS = MiniLockSync_de.ts





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../tools/ucryptlib/libs/ -luCryptLib.Release
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../tools/ucryptlib/libs/ -luCryptLib.Released
#else:unix: LIBS += -L$$PWD/../tools/ucryptlib/libs/ -luCryptLib.Release

win32 {
  INCLUDEPATH += $$PWD/../tools/ucryptlib/ucryptlib/ucryptlib
  DEPENDPATH += $$PWD/../tools/ucryptlib/ucryptlib/ucryptlib
}

unix {
  INCLUDEPATH += "$$_PRO_FILE_PWD_/../tools/uCryptLib"
  DEPENDPATH += "$$_PRO_FILE_PWD_/../tools/uCryptLib"
  LIBS += -L"$$_PRO_FILE_PWD_/../tools/uCryptLib-lib"
  LIBS += -luCryptLib
}
