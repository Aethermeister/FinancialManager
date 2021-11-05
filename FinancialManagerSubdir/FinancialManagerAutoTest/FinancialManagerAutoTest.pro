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
    Authentication/tst_loginwidgettest.cpp \
    Authentication/tst_signupwidgettest.cpp \
    Core/tst_defines.cpp \
    Core/tst_encrypt.cpp \
    Core/tst_widgetdefines.cpp \
    testMain.cpp

HEADERS += \
    Authentication/tst_loginwidgettest.h \
    Authentication/tst_signupwidgettest.h \
    Core/tst_defines.h \
    Core/tst_encrypt.h \
    Core/tst_widgetdefines.h \
    TestUtils.h
