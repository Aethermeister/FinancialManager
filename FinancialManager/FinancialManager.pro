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
    Content/Components/revertrecordwidget.cpp \
    Content/contentwidget.cpp \
    Content/newrecordwidget.cpp \
    Content/overviewwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    user.cpp \
    widgetstylebase.cpp

HEADERS += \
    Authentication/authenticationcomponent.h \
    Authentication/authenticationwidget.h \
    Authentication/loginwidget.h \
    Authentication/signupwidget.h \
    Content/Components/revertrecordwidget.h \
    Content/contentwidget.h \
    Content/newrecordwidget.h \
    Content/overviewwidget.h \
    Core/defines.h \
    defines.h \
    mainwindow.h \
    user.h \
    widgetstylebase.h

FORMS += \
    Authentication/authenticationwidget.ui \
    Authentication/loginwidget.ui \
    Authentication/signupwidget.ui \
    Content/Components/revertrecordwidget.ui \
    Content/contentwidget.ui \
    Content/newrecordwidget.ui \
    Content/overviewwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/resources.qrc
