QT += testlib
QT += core gui charts
CONFIG += qt warn_on depend_includepath testcase

CONFIG(debug, debug|release) {
        DESTDIR = ../Build/Debug
}

CONFIG(release, debug|release) {
        DESTDIR = ../Build/Release
}

INCLUDEPATH += $$PWD/../FinancialManagerLibrary
LIBS += $$DESTDIR/FinancialManagerLibrary.lib

TEMPLATE = app

SOURCES +=  tst_core.cpp
