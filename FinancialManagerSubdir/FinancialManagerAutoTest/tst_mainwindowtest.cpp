#include "tst_mainwindowtest.h"
#include "TestUtils.h"
#include "Core/defines.h"
#include "mainwindow.h"
#include "Authentication/loginwidget.h"
#include "Content/contentwidget.h"
#include "Content/profilewidget.h"

void MainWindowTest::initTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void MainWindowTest::cleanupTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void MainWindowTest::test_mainWindowContents()
{
    writeJSONFile(USERSFILE, QJsonDocument(testData));

    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();

    auto loginWidget = mainWindow->containerWidget()->findChild<Authentication::LoginWidget*>();
    QVERIFY(loginWidget);
    QVERIFY(mainWindow->profilButton()->isHidden());

    loginWidget->usernameLineEdit()->setText(username);
    loginWidget->passwordLineEdit()->setText(password);
    loginWidget->loginButton()->click();

    auto contentWidget = mainWindow->findChild<Content::ContentWidget*>();
    QVERIFY(contentWidget);
    QVERIFY(mainWindow->profilButton()->isVisible());
    QVERIFY(mainWindow->titleLabel()->text().endsWith("- " + username));

    mainWindow->profilButton()->click();
    QVERIFY(contentWidget->findChild<Content::ProfileWidget*>());

    mainWindow->deleteLater();
}
