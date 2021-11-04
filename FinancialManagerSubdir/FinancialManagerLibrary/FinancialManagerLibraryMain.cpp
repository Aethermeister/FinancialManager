#include "mainwindow.h"
#include "FinancialManagerLibraryMain.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

int libraryMain(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setWindowIcon(QIcon("://Images/diamond.ico"));

    QCoreApplication::setApplicationName("Financial Manager");
    QCoreApplication::setOrganizationName("Aether Projects");
    QCoreApplication::setOrganizationDomain("Aether Projects");
    QCoreApplication::setApplicationVersion("1.0");

    //Check (and create if needed) appdata folder
    checkFolderExistence(APPLICATIONFOLDER());
    //Check (and create if needed) users file
    checkFileExistence(USERSFILE);

    QFile styleFile(":/Styles/default.qss");
    styleFile.open(QFile::ReadOnly);
    a.setStyleSheet(styleFile.readAll());

    MainWindow w;
    w.show();
    return a.exec();
}
