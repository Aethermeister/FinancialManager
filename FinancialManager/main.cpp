#include "mainwindow.h"
#include "Core/defines.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("Financial Manager");
    QCoreApplication::setOrganizationName("Aether Projects");
    QCoreApplication::setOrganizationDomain("Aether Projects");
    QCoreApplication::setApplicationVersion("1.0");

    //Check (and create if needed) appdata folder
    checkFolderExistence(APPDATALOCATION());
    //Check (and create if needed) needed users file
    checkFileExistence(USERSFILE);

    QFile styleFile(":/Styles/default.qss");
    styleFile.open(QFile::ReadOnly);
    a.setStyleSheet(styleFile.readAll());

    MainWindow w;
    w.show();
    return a.exec();
}
