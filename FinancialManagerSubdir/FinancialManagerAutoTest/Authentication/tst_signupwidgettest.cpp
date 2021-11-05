#include "tst_signupwidgettest.h"
#include "TestUtils.h"


void SignUpWidgetTest::initTestCase()
{
    deleteFile(USERSFILE);
    makeFolder(APPLICATIONFOLDER());
}

void SignUpWidgetTest::cleanupTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void SignUpWidgetTest::init()
{
    deleteFile(USERSFILE);
    makeFolder(APPLICATIONFOLDER());
}

void SignUpWidgetTest::cleanup()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void SignUpWidgetTest::test_initializeUi()
{
    Authentication::SignUpWidget* signUpWidget = new Authentication::SignUpWidget();
    signUpWidget->show();
    QVERIFY(signUpWidget->informationLabel()->isHidden());

    signUpWidget->deleteLater();
}

void SignUpWidgetTest::test_signUpFalse()
{
    writeJSONFile(USERSFILE, QJsonDocument(testData));

    Authentication::SignUpWidget* signUpWidget = new Authentication::SignUpWidget();
    signUpWidget->show();

    signUpWidget->signUpButton()->click();
    QVERIFY(signUpWidget->informationLabel()->isVisible());
    QCOMPARE(signUpWidget->informationLabel()->text(), "Username cannot be empty");

    signUpWidget->usernameLineEdit()->setText(username);
    signUpWidget->signUpButton()->click();
    QVERIFY(signUpWidget->informationLabel()->isVisible());
    QCOMPARE(signUpWidget->informationLabel()->text(), "Password has to contain at least 6 characters");

    signUpWidget->usernameLineEdit()->setText(username);
    signUpWidget->passwordLineEdit()->setText(password);
    signUpWidget->signUpButton()->click();
    QVERIFY(signUpWidget->informationLabel()->isVisible());
    QCOMPARE(signUpWidget->informationLabel()->text(), "Passwords do not match");

    signUpWidget->usernameLineEdit()->setText(username);
    signUpWidget->passwordLineEdit()->setText(password);
    signUpWidget->verifyPasswordLineEdit()->setText(password);
    signUpWidget->signUpButton()->click();
    QVERIFY(signUpWidget->informationLabel()->isVisible());
    QCOMPARE(signUpWidget->informationLabel()->text(), "Username is already used");

    signUpWidget->deleteLater();
}

void SignUpWidgetTest::test_signUpTrue()
{
    Authentication::SignUpWidget* signUpWidget = new Authentication::SignUpWidget();
    signUpWidget->show();

    signUpWidget->usernameLineEdit()->setText(username);
    signUpWidget->passwordLineEdit()->setText(password);
    signUpWidget->verifyPasswordLineEdit()->setText(password);

    signUpWidget->signUpButton()->click();
    QVERIFY(signUpWidget->informationLabel()->isHidden());

    const auto usersDocument = readJSONFile(USERSFILE);
    const auto usersObject = usersDocument.object();
    QVERIFY(usersObject.contains(username));

    signUpWidget->deleteLater();
}
