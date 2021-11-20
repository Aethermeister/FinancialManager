#include "tst_newrecordwidgettest.h"
#include "TestUtils.h"
#include "Core/defines.h"
#include "Content/Records/newrecordwidget.h"
#include "Content/History/Components/recordhistoryitemwidget.h"

void NewRecordWidgetTest::initTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void NewRecordWidgetTest::cleanupTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void NewRecordWidgetTest::init()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void NewRecordWidgetTest::cleanup()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void NewRecordWidgetTest::test_defaultUi()
{
    const auto testUserDataPath = APPLICATIONFOLDER() + "\\" + id;
    makeFolder(testUserDataPath);
    QFile::copy("://UserFiles/pockets.json", testUserDataPath + "\\pockets.json");
    QFile::copy("://UserFiles/records.json", testUserDataPath + "\\records.json");

    auto user = std::make_shared<User>(username, password, id);
    Content::Records::NewRecordWidget* newRecordWidget = new  Content::Records::NewRecordWidget(user);
    newRecordWidget->show();

    const auto currentDateTime = QDateTime::currentDateTime();

    QVERIFY(newRecordWidget->recordValueLineEdit()->text().isEmpty());
    QVERIFY(newRecordWidget->recordItemLineEdit()->text().isEmpty());
    QVERIFY(newRecordWidget->recordLocationLineEdit()->text().isEmpty());
    QVERIFY(newRecordWidget->recordPocketComboBox()->currentText().isEmpty());
    QCOMPARE(newRecordWidget->recordPocketComboBox()->count(), user->pockets().size());

    QCOMPARE(newRecordWidget->yearLineEdit()->text().toInt(), currentDateTime.date().year());
    QCOMPARE(newRecordWidget->monthLineEdit()->text().toInt(), currentDateTime.date().month());
    QCOMPARE(newRecordWidget->dayLineEdit()->text().toInt(), currentDateTime.date().day());

    QCOMPARE(newRecordWidget->hoursLineEdit()->text().toInt(), currentDateTime.time().hour());
    QCOMPARE(newRecordWidget->minutesLineEdit()->text().toInt(), currentDateTime.time().minute());

    QCOMPARE(newRecordWidget->historyListingWidget()->findChildren<Content::History::Component::RecordHistoryItemWidget*>().size(), 10);
}

void NewRecordWidgetTest::test_createNewRecord()
{
    auto user = std::make_shared<User>(username, password, id);
    Content::Records::NewRecordWidget* newRecordWidget = new  Content::Records::NewRecordWidget(user);
    newRecordWidget->show();

    newRecordWidget->recordValueLineEdit()->setText("1500");
    newRecordWidget->recordItemLineEdit()->setText("test");
    newRecordWidget->recordLocationLineEdit()->setText("test");
    newRecordWidget->recordPocketComboBox()->setCurrentIndex(0);

    newRecordWidget->submitRecordButton()->click();
}
