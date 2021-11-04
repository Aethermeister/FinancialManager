QT += testlib
QT += core gui charts
CONFIG += c++11 c++17 qt warn_on depend_includepath testcase

CONFIG(debug, debug|release) {
        DESTDIR = ../../Build/Debug
}

CONFIG(release, debug|release) {
        DESTDIR = ../../Build/Release
}

INCLUDEPATH += $$PWD/../FinancialManagerLibrary
LIBS += $$DESTDIR/FinancialManagerLibrary.lib

TEMPLATE = app

SOURCES +=  \
    testMain.cpp \
    tst_encrypt.cpp \
    tst_widgetdefines.cpp

HEADERS += \
    tst_encrypt.h \
    tst_widgetdefines.h
