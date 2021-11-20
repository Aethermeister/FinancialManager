#include "tst_contentwidgettest.h"
#include "TestUtils.h"
#include "Core/defines.h"
#include "Content/contentwidget.h"
#include "Content/Overview/overviewwidget.h"
#include "Content/Pockets/pocketswidget.h"
#include "Content/Records/newrecordwidget.h"
#include "Content/History/recordshistorywidget.h"
#include "Content/Statistics/statisticswidget.h"

void ContentWidgetTest::initTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void ContentWidgetTest::cleanupTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void ContentWidgetTest::test_contentWidgets()
{
    auto user = std::make_shared<User>(username, password, id);
    Content::ContentWidget* contentWidget = new Content::ContentWidget(user);
    contentWidget->show();

    QVERIFY(contentWidget->findChild<Content::Overview::OverviewWidget*>());
    QVERIFY(contentWidget->overviewButton()->isChecked());

    contentWidget->pocketsButton()->click();
    QVERIFY(contentWidget->findChild<Content::Pockets::PocketsWidget*>());
    QVERIFY(contentWidget->pocketsButton()->isChecked());

    contentWidget->newRecordButton()->click();
    QVERIFY(contentWidget->findChild<Content::Records::NewRecordWidget*>());
    QVERIFY(contentWidget->newRecordButton()->isChecked());

    contentWidget->historyButton()->click();
    QVERIFY(contentWidget->findChild<Content::History::RecordsHistoryWidget*>());
    QVERIFY(contentWidget->historyButton()->isChecked());

    contentWidget->statisticsButton()->click();
    QVERIFY(contentWidget->findChild<Content::Statistics::StatisticsWidget*>());
    QVERIFY(contentWidget->statisticsButton()->isChecked());

    contentWidget->deleteLater();
}
