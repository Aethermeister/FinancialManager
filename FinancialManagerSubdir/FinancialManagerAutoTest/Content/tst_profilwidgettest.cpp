#include "tst_profilwidgettest.h"
#include "TestUtils.h"
#include "Core/defines.h"
#include "user.h"

void ProfilWidgetTest::initTestCase()
{
    deleteFile(USERSFILE);
    makeFolder(APPLICATIONFOLDER());
}

void ProfilWidgetTest::cleanupTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void ProfilWidgetTest::test_initializeUiDefault()
{
    auto user = std::make_shared<User>(username, password, id);

    Content::ProfileWidget* profilWidget = new Content::ProfileWidget(user);
    profilWidget->show();

    QCOMPARE(profilWidget->usernameLabel()->text(), username);
    QCOMPARE(profilWidget->idLabel()->text(), id);

    QVERIFY(profilWidget->passwordInformationLabel()->isHidden());
    QVERIFY(profilWidget->deletionInformationLabel()->isHidden());

    QVERIFY(profilWidget->deleteAccountButton()->isVisible());
    QVERIFY(profilWidget->cancelDeletionButton()->isHidden());

    profilWidget->deleteLater();
}

void ProfilWidgetTest::test_initializeUiWithDeletion()
{
    auto user = std::make_shared<User>(username, password, id);
    user->setMarkedForDeletion(true);

    Content::ProfileWidget* profilWidget = new Content::ProfileWidget(user);
    profilWidget->show();

    QCOMPARE(profilWidget->usernameLabel()->text(), username);
    QCOMPARE(profilWidget->idLabel()->text(), id);

    QVERIFY(profilWidget->passwordInformationLabel()->isHidden());
    QVERIFY(profilWidget->deletionInformationLabel()->isVisible());

    QVERIFY(profilWidget->deleteAccountButton()->isHidden());
    QVERIFY(profilWidget->cancelDeletionButton()->isVisible());

    profilWidget->deleteLater();
}

void ProfilWidgetTest::test_changePasswordFalse()
{
    auto user = std::make_shared<User>(username, password, id);

    Content::ProfileWidget* profilWidget = new Content::ProfileWidget(user);
    profilWidget->show();

    profilWidget->changePasswordButton()->click();
    QVERIFY(profilWidget->passwordInformationLabel()->isVisible());
    QCOMPARE(profilWidget->passwordInformationLabel()->text(), "Incorrect old password");
    QCOMPARE(user->password(), password);

    profilWidget->oldPasswordLineEdit()->setText(password);
    profilWidget->newPasswordLineEdit()->setText(password);
    profilWidget->changePasswordButton()->click();
    QVERIFY(profilWidget->passwordInformationLabel()->isVisible());
    QCOMPARE(profilWidget->passwordInformationLabel()->text(), "New password cannot be the same as the old one");
    QCOMPARE(user->password(), password);

    const QString newBadPassword = "test_user";
    profilWidget->oldPasswordLineEdit()->setText(password);
    profilWidget->newPasswordLineEdit()->setText(newBadPassword);
    profilWidget->changePasswordButton()->click();
    QVERIFY(profilWidget->passwordInformationLabel()->isVisible());
    QCOMPARE(profilWidget->passwordInformationLabel()->text(), "Password has to contain 8-32 characters.\nIt has to contain lower and uppercase letters and digits");
    QCOMPARE(user->password(), password);

    const QString newGoodPassword = "test_userAAA000";
    profilWidget->oldPasswordLineEdit()->setText(password);
    profilWidget->newPasswordLineEdit()->setText(newGoodPassword);
    profilWidget->changePasswordButton()->click();
    QVERIFY(profilWidget->passwordInformationLabel()->isVisible());
    QCOMPARE(profilWidget->passwordInformationLabel()->text(), "New passwords do not match");
    QCOMPARE(user->password(), password);

    profilWidget->deleteLater();
}

void ProfilWidgetTest::test_changePasswordTrue()
{
    writeJSONFile(USERSFILE, QJsonDocument(testData));

    auto user = std::make_shared<User>(username, password, id);

    Content::ProfileWidget* profilWidget = new Content::ProfileWidget(user);
    profilWidget->show();

    const QString newPassword = "test_userAAA000";
    profilWidget->oldPasswordLineEdit()->setText(password);
    profilWidget->newPasswordLineEdit()->setText(newPassword);
    profilWidget->verifyNewPasswordLineEdit()->setText(newPassword);
    profilWidget->changePasswordButton()->click();
    QVERIFY(profilWidget->passwordInformationLabel()->isHidden());
    QCOMPARE(user->password(), newPassword);

    profilWidget->deleteLater();
}

void ProfilWidgetTest::test_deleteAccount()
{
    writeJSONFile(USERSFILE, QJsonDocument(testData));

    auto user = std::make_shared<User>(username, password, id);

    Content::ProfileWidget* profilWidget = new Content::ProfileWidget(user);
    profilWidget->show();

    profilWidget->deleteAccountButton()->click();

    QVERIFY(profilWidget->deletionInformationLabel()->isVisible());
    QVERIFY(profilWidget->deleteAccountButton()->isHidden());
    QVERIFY(profilWidget->cancelDeletionButton()->isVisible());

    QVERIFY(user->isMarkedForDeletion());

    profilWidget->deleteLater();
}

void ProfilWidgetTest::test_cancelDeletion()
{
    auto user = std::make_shared<User>(username, password, id);
    user->setMarkedForDeletion(true);

    Content::ProfileWidget* profilWidget = new Content::ProfileWidget(user);
    profilWidget->show();

    profilWidget->cancelDeletionButton()->click();

    QVERIFY(profilWidget->deletionInformationLabel()->isHidden());
    QVERIFY(profilWidget->deleteAccountButton()->isVisible());
    QVERIFY(profilWidget->cancelDeletionButton()->isHidden());

    QVERIFY(!user->isMarkedForDeletion());

    profilWidget->deleteLater();
}
