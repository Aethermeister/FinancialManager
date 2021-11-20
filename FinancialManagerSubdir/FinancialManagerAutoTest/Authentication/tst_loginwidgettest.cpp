#include "tst_loginwidgettest.h"
#include "Authentication/loginwidget.h"
#include "TestUtils.h"

void LoginWidgetTest::initTestCase()
{
    Settings::SettingsManager::instance()->resetSettingsData();

    deleteFile(USERSFILE);
    makeFolder(APPLICATIONFOLDER());
}

void LoginWidgetTest::cleanupTestCase()
{
    Settings::SettingsManager::instance()->resetSettingsData();

    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void LoginWidgetTest::init()
{
    Settings::SettingsManager::instance()->resetSettingsData();

    deleteFile(USERSFILE);
    makeFolder(APPLICATIONFOLDER());
}

void LoginWidgetTest::cleanup()
{
    Settings::SettingsManager::instance()->resetSettingsData();

    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void LoginWidgetTest::test_initializeUiDefault()
{
    Authentication::LoginWidget* loginWidget = new Authentication::LoginWidget();
    loginWidget->show();

    QVERIFY(loginWidget->usernameLineEdit()->text().isEmpty());
    QVERIFY(loginWidget->passwordLineEdit()->text().isEmpty());
    QVERIFY(!loginWidget->rememberMeCheckBox()->isChecked());

    loginWidget->deleteLater();
}

void LoginWidgetTest::test_initializeUiWithSettingsData()
{
    writeJSONFile(USERSFILE, QJsonDocument(testData));

    Settings::SettingsManager::instance()->setData(Settings::SettingsData::REMEMBER_ME, true);
    Settings::SettingsManager::instance()->setData(Settings::SettingsData::LAST_USER_NAME, username);

    Authentication::LoginWidget* loginWidget = new Authentication::LoginWidget();
    loginWidget->show();

    QCOMPARE(loginWidget->usernameLineEdit()->text(), username);
    QCOMPARE(loginWidget->passwordLineEdit()->text(), password);
    QVERIFY(loginWidget->rememberMeCheckBox()->isChecked());

    loginWidget->deleteLater();
}

void LoginWidgetTest::test_loginFalse()
{
    Authentication::LoginWidget* loginWidget = new Authentication::LoginWidget();
    loginWidget->show();

    QVERIFY(loginWidget->informationLabel()->isHidden());

    loginWidget->loginButton()->click();
    QVERIFY(loginWidget->informationLabel()->isVisible());
    QCOMPARE(loginWidget->informationLabel()->text(), "Username is empty");

    loginWidget->usernameLineEdit()->setText(username);
    loginWidget->loginButton()->click();
    QVERIFY(loginWidget->informationLabel()->isVisible());
    QCOMPARE(loginWidget->informationLabel()->text(), "Password is empty");

    loginWidget->usernameLineEdit()->setText(username);
    loginWidget->passwordLineEdit()->setText(password);
    loginWidget->loginButton()->click();
    QVERIFY(loginWidget->informationLabel()->isVisible());
    QCOMPARE(loginWidget->informationLabel()->text(), "Incorrect username and/or password");

    loginWidget->deleteLater();
}

void LoginWidgetTest::test_loginTrue()
{
    writeJSONFile(USERSFILE, QJsonDocument(testData));

    Authentication::LoginWidget* loginWidget = new Authentication::LoginWidget();
    loginWidget->show();

    loginWidget->rememberMeCheckBox()->click();

    loginWidget->usernameLineEdit()->setText(username);
    loginWidget->passwordLineEdit()->setText(password);

    loginWidget->loginButton()->click();
    QVERIFY(loginWidget->informationLabel()->isHidden());

    const auto storedRememberMeState = Settings::SettingsManager::instance()->data<bool>(Settings::SettingsData::REMEMBER_ME);
    const auto storedLastUsername = Settings::SettingsManager::instance()->data<QString>(Settings::SettingsData::LAST_USER_NAME);
    QVERIFY(storedRememberMeState);
    QCOMPARE(storedLastUsername, username);

    loginWidget->deleteLater();
}
