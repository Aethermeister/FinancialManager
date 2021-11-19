#include "tst_overviewwidgettest.h"
#include "TestUtils.h"
#include "Core/defines.h"
#include "Content/Overview/overviewwidget.h"
#include "Content/Overview/Components/generaloverviewmessagewidget.h"
#include "Content/Overview/Components/statisticsoverviewwidget.h"

void OverviewWidgetTest::initTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void OverviewWidgetTest::cleanupTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void OverviewWidgetTest::init()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void OverviewWidgetTest::cleanup()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void OverviewWidgetTest::test_overviewWidgetWithNewUser()
{
    auto user = std::make_shared<User>(username, password, id);
    Content::Overview::OverviewWidget* overviewWidget = new Content::Overview::OverviewWidget(user);

    auto generalOverviewWidget = overviewWidget->findChild<Content::Overview::Components::GeneralOverviewMessageWidget*>();
    auto statisticsOverviewWidget = overviewWidget->findChild<Content::Overview::Components::StatisticsOverviewWidget*>();

    QVERIFY(generalOverviewWidget);
    QVERIFY(!statisticsOverviewWidget);

    overviewWidget->deleteLater();
}

void OverviewWidgetTest::test_overviewWidgetWithOldUser()
{
    const auto testUserDataPath = APPLICATIONFOLDER() + "\\" + id;
    makeFolder(testUserDataPath);
    QFile::copy("://UserFiles/pockets.json", testUserDataPath + "\\pockets.json");
    QFile::copy("://UserFiles/records.json", testUserDataPath + "\\records.json");

    auto user = std::make_shared<User>(username, password, id);
    Content::Overview::OverviewWidget* overviewWidget = new Content::Overview::OverviewWidget(user);

    auto generalOverviewWidget = overviewWidget->findChild<Content::Overview::Components::GeneralOverviewMessageWidget*>();
    auto statisticsOverviewWidget = overviewWidget->findChild<Content::Overview::Components::StatisticsOverviewWidget*>();

    QVERIFY(!generalOverviewWidget);
    QVERIFY(statisticsOverviewWidget);

    overviewWidget->deleteLater();
}
