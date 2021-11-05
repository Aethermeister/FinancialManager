#include "Core/tst_widgetdefines.h"
#include "Core/tst_encrypt.h"
#include "Core/tst_defines.h"
#include "Authentication/tst_signupwidgettest.h"
#include "Authentication/tst_loginwidgettest.h"

#include <QtTest>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Set the application properties so it does not modify the original registry entirs and AppData files
    QCoreApplication::setApplicationName("Financial Manager Test");
    QCoreApplication::setOrganizationName("Aether Projects");
    QCoreApplication::setOrganizationDomain("Aether Projects");
    QCoreApplication::setApplicationVersion("1.0");

    //Create a clean state for the tests
    QDir(APPLICATIONFOLDER()).removeRecursively();
    checkFolderExistence(APPLICATIONFOLDER());
    Settings::SettingsManager::instance()->resetSettingsData();

    Test::Core::WidgetDefinesTest widgetDefinesTest;
    Test::Core::EncryptTest encryptTest;
    Test::Core::DefinesTest definesTest;
    SignUpWidgetTest signUpWidgetTest;
    LoginWidgetTest loginWidgetTest;

    return
            (
                QTest::qExec(&widgetDefinesTest, argc, argv) ||
                QTest::qExec(&encryptTest, argc, argv) ||
                QTest::qExec(&definesTest, argc, argv) ||
                QTest::qExec(&signUpWidgetTest, argc, argv) ||
                QTest::qExec(&loginWidgetTest, argc, argv)
            );
}
