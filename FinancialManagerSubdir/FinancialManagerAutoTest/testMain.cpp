#include "Core/tst_widgetdefines.h"
#include "Core/tst_encrypt.h"
#include "Core/tst_defines.h"
#include "Settings/tst_settingswindowtest.h"
#include "Settings/tst_customfilestoragewidgettest.h"
#include "Authentication/tst_signupwidgettest.h"
#include "Authentication/tst_loginwidgettest.h"
#include "Authentication/tst_authenticationwidgettest.h"
#include "Content/tst_profilwidgettest.h"
#include "Notification/tst_notificationwidgettest.h"
#include "Notification/tst_revertrecordwidgettest.h"
#include "Content/tst_contentwidgettest.h"
#include "tst_mainwindowtest.h"
#include "Content/Overview/tst_overviewwidgettest.h"
#include "Content/Pockets/tst_pocketsdeletiondialogtest.h"
#include "Content/Pockets/tst_pocketswidgettest.h"
#include "Content/Records/tst_newrecordwidgettest.h"
#include "Content/History/tst_recordshistorywidgettest.h"

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
    SettingsWindowTest settingsWindowTest;
    CustomFileStorageWidgetTest customFileStorageWidgetTest;
    SignUpWidgetTest signUpWidgetTest;
    LoginWidgetTest loginWidgetTest;
    AuthenticationWidgetTest authenticationWidgetTest;
    ProfilWidgetTest profilWidgetTest;
    NotificationWidgetTest notificationWidgetTest;
    RevertRecordWidgetTest revertRecordWidgetTest;
    MainWindowTest mainWindowTest;
    ContentWidgetTest contentWidgetTest;
    OverviewWidgetTest overviewWidgetTest;
    PocketsDeletionDialogTest pocketsDeletionDialogTest;
    PocketsWidgetTest pocketsWidgetTest;
    NewRecordWidgetTest newRecordWidgetTest;
    RecordsHistoryWidgetTest recordsHistoryWidgetTest;

    return
            (
                QTest::qExec(&widgetDefinesTest, argc, argv) ||
                QTest::qExec(&encryptTest, argc, argv) ||
                QTest::qExec(&definesTest, argc, argv) ||
                QTest::qExec(&settingsWindowTest, argc, argv) ||
                QTest::qExec(&customFileStorageWidgetTest, argc, argv) ||
                QTest::qExec(&signUpWidgetTest, argc, argv) ||
                QTest::qExec(&loginWidgetTest, argc, argv) ||
                QTest::qExec(&authenticationWidgetTest, argc, argv) ||
                QTest::qExec(&profilWidgetTest, argc, argv) ||
                QTest::qExec(&notificationWidgetTest, argc, argv) ||
                QTest::qExec(&revertRecordWidgetTest, argc, argv) ||
                QTest::qExec(&mainWindowTest, argc, argv) ||
                QTest::qExec(&contentWidgetTest, argc, argv) ||
                QTest::qExec(&overviewWidgetTest, argc, argv) ||
                QTest::qExec(&pocketsDeletionDialogTest, argc, argv) ||
                QTest::qExec(&pocketsWidgetTest, argc, argv) ||
                QTest::qExec(&newRecordWidgetTest, argc, argv) ||
                QTest::qExec(&recordsHistoryWidgetTest, argc, argv)
            );
}
