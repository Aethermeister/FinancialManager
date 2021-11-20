#include "tst_recordshistorywidgettest.h"
#include "TestUtils.h"
#include "Core/defines.h"
#include "Content/History/recordshistorywidget.h"

void RecordsHistoryWidgetTest::initTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void RecordsHistoryWidgetTest::cleanupTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void RecordsHistoryWidgetTest::init()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void RecordsHistoryWidgetTest::cleanup()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void RecordsHistoryWidgetTest::test_defaultUi()
{
    const auto testUserDataPath = APPLICATIONFOLDER() + "\\" + id;
    makeFolder(testUserDataPath);
    QFile::copy("://UserFiles/pockets.json", testUserDataPath + "\\pockets.json");
    QFile::copy("://UserFiles/records.json", testUserDataPath + "\\records.json");

    auto user = std::make_shared<User>(username, password, id);
    Content::History::RecordsHistoryWidget* recordsHistoryWidget = new Content::History::RecordsHistoryWidget(user);
    recordsHistoryWidget->show();

    QCOMPARE(recordsHistoryWidget->historyListingWidget()->findChildren<Content::History::Component::RecordHistoryItemWidget*>().size(), user->records().size());

    QVERIFY(recordsHistoryWidget->filterWidget()->isHidden());
    QVERIFY(recordsHistoryWidget->recordContentWidget()->isHidden());

    recordsHistoryWidget->deleteLater();
}

void RecordsHistoryWidgetTest::test_deleteRecord()
{
    const auto testUserDataPath = APPLICATIONFOLDER() + "\\" + id;
    makeFolder(testUserDataPath);
    QFile::copy("://UserFiles/pockets.json", testUserDataPath + "\\pockets.json");
    QFile::copy("://UserFiles/records.json", testUserDataPath + "\\records.json");

    auto user = std::make_shared<User>(username, password, id);
    const auto originalRecordsCount = user->records().size();

    Content::History::RecordsHistoryWidget* recordsHistoryWidget = new Content::History::RecordsHistoryWidget(user);
    recordsHistoryWidget->show();

    const auto& recordItems = recordsHistoryWidget->historyListingWidget()->findChildren<Content::History::Component::RecordHistoryItemWidget*>();
    const auto firstRecordItem = recordItems.front();

    firstRecordItem->setMouseOver(true);
    QTest::mouseClick(firstRecordItem, Qt::LeftButton);
    QVERIFY(recordsHistoryWidget->recordContentWidget()->isVisible());

    recordsHistoryWidget->recordContentWidget()->deleteRecordButton()->click();
    QVERIFY(recordsHistoryWidget->recordContentWidget()->isHidden());

    QCOMPARE(recordsHistoryWidget->historyListingWidget()->findChildren<Content::History::Component::RecordHistoryItemWidget*>().size(), originalRecordsCount - 1);
    QCOMPARE(user->records().size(), originalRecordsCount - 1);

    recordsHistoryWidget->deleteLater();
}

void RecordsHistoryWidgetTest::test_filterHistoryList()
{
    const auto testUserDataPath = APPLICATIONFOLDER() + "\\" + id;
    makeFolder(testUserDataPath);
    QFile::copy("://UserFiles/pockets.json", testUserDataPath + "\\pockets.json");
    QFile::copy("://UserFiles/records.json", testUserDataPath + "\\records.json");

    auto user = std::make_shared<User>(username, password, id);

    Content::History::RecordsHistoryWidget* recordsHistoryWidget = new Content::History::RecordsHistoryWidget(user);
    recordsHistoryWidget->show();

    recordsHistoryWidget->filterButton()->click();
    QVERIFY(recordsHistoryWidget->filterWidget()->isVisible());

    const auto& recordItems = recordsHistoryWidget->historyListingWidget()->findChildren<Content::History::Component::RecordHistoryItemWidget*>();
    const auto firstRecordItem = recordItems.front();
    const auto& itemFilter = firstRecordItem->record().item();

    recordsHistoryWidget->filterWidget()->itemFilterLineEdit()->setText(itemFilter);
    emit recordsHistoryWidget->filterWidget()->itemFilterLineEdit()->editingFinished();

    for(const auto& recordItem : recordItems)
    {
        if(recordItem->record().item() == itemFilter)
        {
            QVERIFY(recordItem->isVisible());
        }
        else
        {
            QVERIFY(recordItem->isHidden());
        }
    }

    recordsHistoryWidget->deleteLater();
}
