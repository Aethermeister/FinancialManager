QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 c++17

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
    Content/contentwidget.cpp \
    Content/newrecordwidget.cpp \
    Content/overviewwidget.cpp \
    Content/profilewidget.cpp \
    Notification/notificationbase.cpp \
    Notification/notificationwidget.cpp \
    Notification/revertrecordwidget.cpp \
    Settings/customfilestoragewidget.cpp \
    Settings/localfilestoragewidget.cpp \
    Settings/settingsmanager.cpp \
    Settings/settingswindow.cpp \
    main.cpp \
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
    Content/contentwidget.h \
    Content/newrecordwidget.h \
    Content/overviewwidget.h \
    Content/profilewidget.h \
    Core/defines.h \
    Core/encrypt.h \
    Core/widgetdefines.h \
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
    Content/contentwidget.ui \
    Content/newrecordwidget.ui \
    Content/overviewwidget.ui \
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
