QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 c++17

CONFIG(debug, debug|release) {
        DESTDIR = ../../Build/Debug
}

CONFIG(release, debug|release) {
        DESTDIR = ../../Build/Release
}

QMAKE_CXXFLAGS_RELEASE += /Zi
QMAKE_LFLAGS_RELEASE += /DEBUG

TEMPLATE = lib

DEFINES += MAKE_LIB_EXPORT

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += c:/emsdk/emsdk/upstream/emscripten/system/include

SOURCES += \
    Authentication/authenticationcomponent.cpp \
    Authentication/authenticationwidget.cpp \
    Authentication/loginwidget.cpp \
    Authentication/signupwidget.cpp \
    Content/History/Components/historyfilterwidget.cpp \
    Content/History/Components/historylistingwidget.cpp \
    Content/History/Components/recordcontentwidget.cpp \
    Content/History/Components/recordhistoryitemwidget.cpp \
    Content/History/recordshistorywidget.cpp \
    Content/Overview/Components/generaloverviewmessagewidget.cpp \
    Content/Overview/Components/statisticsoverviewwidget.cpp \
    Content/Overview/overviewwidget.cpp \
    Content/Pockets/Components/pocketdeletiondialog.cpp \
    Content/Pockets/Components/pocketlistingwidget.cpp \
    Content/Pockets/Components/pocketlistitemwidget.cpp \
    Content/Pockets/pocket.cpp \
    Content/Pockets/pocketswidget.cpp \
    Content/Records/newrecordwidget.cpp \
    Content/Records/record.cpp \
    Content/Statistics/Components/cashflowchartview.cpp \
    Content/Statistics/Components/chartviewbase.cpp \
    Content/Statistics/Components/piechartview.cpp \
    Content/Statistics/Components/pocketsvaluechartview.cpp \
    Content/Statistics/Components/recordsdatachartview.cpp \
    Content/Statistics/statisticsselectionwidget.cpp \
    Content/Statistics/statisticswidget.cpp \
    Content/contentwidget.cpp \
    Content/profilewidget.cpp \
    FinancialManagerLibraryMain.cpp \
    Notification/notificationbase.cpp \
    Notification/notificationwidget.cpp \
    Notification/revertrecordwidget.cpp \
    Settings/customfilestoragewidget.cpp \
    Settings/localfilestoragewidget.cpp \
    Settings/settingsmanager.cpp \
    Settings/settingswindow.cpp \
    mainwindow.cpp \
    user.cpp

HEADERS += \
    Authentication/authenticationcomponent.h \
    Authentication/authenticationwidget.h \
    Authentication/loginwidget.h \
    Authentication/signupwidget.h \
    Content/History/Components/historyfilterwidget.h \
    Content/History/Components/historylistingwidget.h \
    Content/History/Components/recordcontentwidget.h \
    Content/History/Components/recordhistoryitemwidget.h \
    Content/History/recordshistorywidget.h \
    Content/Overview/Components/generaloverviewmessagewidget.h \
    Content/Overview/Components/statisticsoverviewwidget.h \
    Content/Overview/overviewwidget.h \
    Content/Pockets/Components/pocketdeletiondialog.h \
    Content/Pockets/Components/pocketlistingwidget.h \
    Content/Pockets/Components/pocketlistitemwidget.h \
    Content/Pockets/pocket.h \
    Content/Pockets/pocketswidget.h \
    Content/Records/newrecordwidget.h \
    Content/Records/record.h \
    Content/Statistics/Components/cashflowchartview.h \
    Content/Statistics/Components/chartviewbase.h \
    Content/Statistics/Components/piechartview.h \
    Content/Statistics/Components/pocketsvaluechartview.h \
    Content/Statistics/Components/recordsdatachartview.h \
    Content/Statistics/statisticsselectionwidget.h \
    Content/Statistics/statisticswidget.h \
    Content/contentwidget.h \
    Content/profilewidget.h \
    Core/defines.h \
    Core/encrypt.h \
    Core/global_defines.h \
    Core/widgetdefines.h \
    FinancialManagerLibraryMain.h \
    Notification/notificationbase.h \
    Notification/notificationwidget.h \
    Notification/revertrecordwidget.h \
    Settings/customfilestoragewidget.h \
    Settings/localfilestoragewidget.h \
    Settings/settingsmanager.h \
    Settings/settingswindow.h \
    defines.h \
    mainwindow.h \
    user.h

FORMS += \
    Authentication/authenticationwidget.ui \
    Authentication/loginwidget.ui \
    Authentication/signupwidget.ui \
    Content/History/Components/historyfilterwidget.ui \
    Content/History/Components/historylistingwidget.ui \
    Content/History/Components/recordcontentwidget.ui \
    Content/History/Components/recordhistoryitemwidget.ui \
    Content/History/recordshistorywidget.ui \
    Content/Overview/Components/generaloverviewmessagewidget.ui \
    Content/Overview/Components/statisticsoverviewwidget.ui \
    Content/Overview/overviewwidget.ui \
    Content/Pockets/Components/pocketdeletiondialog.ui \
    Content/Pockets/Components/pocketlistingwidget.ui \
    Content/Pockets/Components/pocketlistitemwidget.ui \
    Content/Pockets/pocketswidget.ui \
    Content/Records/newrecordwidget.ui \
    Content/Statistics/statisticsselectionwidget.ui \
    Content/Statistics/statisticswidget.ui \
    Content/contentwidget.ui \
    Content/profilewidget.ui \
    Notification/notificationwidget.ui \
    Notification/revertrecordwidget.ui \
    Settings/customfilestoragewidget.ui \
    Settings/localfilestoragewidget.ui \
    Settings/settingswindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/resources.qrc
