TEMPLATE = app
TARGET = test
INCLUDEPATH += .

QT = core testlib

CONFIG += testcase

# Input
HEADERS += myclass.h
SOURCES += test_myclass.cpp