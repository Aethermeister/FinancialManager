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
    Authentication/tst_authenticationwidgettest.cpp \
    Authentication/tst_loginwidgettest.cpp \
    Authentication/tst_signupwidgettest.cpp \
    Content/History/tst_recordshistorywidgettest.cpp \
    Content/Overview/tst_overviewwidgettest.cpp \
    Content/Pockets/tst_pocketsdeletiondialogtest.cpp \
    Content/Pockets/tst_pocketswidgettest.cpp \
    Content/Records/tst_newrecordwidgettest.cpp \
    Content/Statistics/tst_statisticswidgettest.cpp \
    Content/tst_contentwidgettest.cpp \
    Content/tst_profilwidgettest.cpp \
    Core/tst_defines.cpp \
    Core/tst_encrypt.cpp \
    Core/tst_widgetdefines.cpp \
    Notification/tst_notificationwidgettest.cpp \
    Notification/tst_revertrecordwidgettest.cpp \
    Settings/tst_customfilestoragewidgettest.cpp \
    Settings/tst_settingswindowtest.cpp \
    testMain.cpp \
    tst_mainwindowtest.cpp

HEADERS += \
    Authentication/tst_authenticationwidgettest.h \
    Authentication/tst_loginwidgettest.h \
    Authentication/tst_signupwidgettest.h \
    Content/History/tst_recordshistorywidgettest.h \
    Content/Overview/tst_overviewwidgettest.h \
    Content/Pockets/tst_pocketsdeletiondialogtest.h \
    Content/Pockets/tst_pocketswidgettest.h \
    Content/Records/tst_newrecordwidgettest.h \
    Content/Statistics/tst_statisticswidgettest.h \
    Content/tst_contentwidgettest.h \
    Content/tst_profilwidgettest.h \
    Core/tst_defines.h \
    Core/tst_encrypt.h \
    Core/tst_widgetdefines.h \
    Notification/tst_notificationwidgettest.h \
    Notification/tst_revertrecordwidgettest.h \
    Settings/tst_customfilestoragewidgettest.h \
    Settings/tst_settingswindowtest.h \
    TestUtils.h \
    tst_mainwindowtest.h

RESOURCES += \
    Resources/TestResources.qrc
