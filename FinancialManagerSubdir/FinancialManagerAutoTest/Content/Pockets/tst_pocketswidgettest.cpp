#include "tst_pocketswidgettest.h"
#include "TestUtils.h"
#include "Core/defines.h"
#include "Content/Pockets/pocketswidget.h"
#include "Content/Pockets/Components/pocketlistitemwidget.h"

void PocketsWidgetTest::initTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void PocketsWidgetTest::cleanupTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void PocketsWidgetTest::init()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void PocketsWidgetTest::cleanup()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void PocketsWidgetTest::test_defaultUi()
{
    const auto testUserDataPath = APPLICATIONFOLDER() + "\\" + id;
    makeFolder(testUserDataPath);
    QFile::copy("://UserFiles/pockets.json", testUserDataPath + "\\pockets.json");
    QFile::copy("://UserFiles/records.json", testUserDataPath + "\\records.json");

    auto user = std::make_shared<User>(username, password, id);
    Content::Pockets::PocketsWidget* pocketsWidget = new Content::Pockets::PocketsWidget(user);
    pocketsWidget->show();

    QVERIFY(pocketsWidget->pocketNameLineEdit()->text().isEmpty());
    QVERIFY(pocketsWidget->pocketInitialValueLineEdit()->text().isEmpty());
    QVERIFY(pocketsWidget->pocketTypeComboBox()->currentText().isEmpty());
    QVERIFY(pocketsWidget->informationLabel()->isHidden());

    QCOMPARE(pocketsWidget->pocketListingWidget()->findChildren<Content::Pockets::Component::PocketListItemWidget*>().size(), user->pockets().size());

    pocketsWidget->deleteLater();
}

void PocketsWidgetTest::test_newPocketFalse()
{
    const auto testUserDataPath = APPLICATIONFOLDER() + "\\" + id;
    makeFolder(testUserDataPath);
    QFile::copy("://UserFiles/pockets.json", testUserDataPath + "\\pockets.json");
    QFile::copy("://UserFiles/records.json", testUserDataPath + "\\records.json");

    auto user = std::make_shared<User>(username, password, id);
    const auto originalPocketCount = user->pockets().size();

    Content::Pockets::PocketsWidget* pocketsWidget = new Content::Pockets::PocketsWidget(user);
    pocketsWidget->show();

    pocketsWidget->createNewPocketButton()->click();
    QVERIFY(pocketsWidget->informationLabel()->isVisible());
    QCOMPARE(pocketsWidget->informationLabel()->text(), "Pocket name cannot be empty");

    pocketsWidget->pocketNameLineEdit()->setText(user->pockets().front().name());
    pocketsWidget->createNewPocketButton()->click();
    QVERIFY(pocketsWidget->informationLabel()->isVisible());
    QCOMPARE(pocketsWidget->informationLabel()->text(), "Pocket with the same name already exists");

    pocketsWidget->pocketNameLineEdit()->setText("test");
    pocketsWidget->createNewPocketButton()->click();
    QVERIFY(pocketsWidget->informationLabel()->isVisible());
    QCOMPARE(pocketsWidget->informationLabel()->text(), "Pocket initial value is invalid");

    pocketsWidget->pocketNameLineEdit()->setText("test");
    pocketsWidget->pocketInitialValueLineEdit()->setText("1500");
    pocketsWidget->createNewPocketButton()->click();
    QVERIFY(pocketsWidget->informationLabel()->isVisible());
    QCOMPARE(pocketsWidget->informationLabel()->text(), "Pocket type cannot be empty");

    QCOMPARE(user->pockets().size(), originalPocketCount);
    QCOMPARE(pocketsWidget->pocketListingWidget()->findChildren<Content::Pockets::Component::PocketListItemWidget*>().size(), originalPocketCount);

    pocketsWidget->deleteLater();
}

void PocketsWidgetTest::test_newPocketTrue()
{
    const auto testUserDataPath = APPLICATIONFOLDER() + "\\" + id;
    makeFolder(testUserDataPath);
    QFile::copy("://UserFiles/pockets.json", testUserDataPath + "\\pockets.json");
    QFile::copy("://UserFiles/records.json", testUserDataPath + "\\records.json");

    auto user = std::make_shared<User>(username, password, id);
    const auto originalPocketCount = user->pockets().size();

    Content::Pockets::PocketsWidget* pocketsWidget = new Content::Pockets::PocketsWidget(user);
    pocketsWidget->show();

    pocketsWidget->pocketNameLineEdit()->setText("test");
    pocketsWidget->pocketInitialValueLineEdit()->setText("1500");
    pocketsWidget->pocketTypeComboBox()->setCurrentIndex(0);

    pocketsWidget->createNewPocketButton()->click();

    QVERIFY(pocketsWidget->informationLabel()->isHidden());

    QCOMPARE(user->pockets().size(), originalPocketCount + 1);
    QCOMPARE(pocketsWidget->pocketListingWidget()->findChildren<Content::Pockets::Component::PocketListItemWidget*>().size(), originalPocketCount + 1);

    pocketsWidget->deleteLater();
}
