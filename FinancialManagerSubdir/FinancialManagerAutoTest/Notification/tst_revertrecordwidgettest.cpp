#include "tst_revertrecordwidgettest.h"
#include "TestUtils.h"
#include "Notification/revertrecordwidget.h"
#include "Core/defines.h"

void RevertRecordWidgetTest::initTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void RevertRecordWidgetTest::cleanupTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void RevertRecordWidgetTest::init()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void RevertRecordWidgetTest::cleanup()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void RevertRecordWidgetTest::test_revertRecord()
{
    const auto testUserDataPath = APPLICATIONFOLDER() + "\\" + id;
    makeFolder(testUserDataPath);
    QFile::copy("://UserFiles/pockets.json", testUserDataPath + "\\pockets.json");
    QFile::copy("://UserFiles/records.json", testUserDataPath + "\\records.json");

    auto user = std::make_shared<User>(username, password, id);
    const auto originalRecordsCount = user->records().size();
    const auto& originalFrontRecord = user->records().front();

    const auto record = Content::Records::Record(1500, QDate::currentDate(), QTime::currentTime(), "test", "test", user->pockets().front().name());

    QWidget* dummyWidget = new QWidget();
    dummyWidget->show();

    Notification::RevertRecordWidget* revertRecordWidget = new Notification::RevertRecordWidget(record, user, dummyWidget);
    revertRecordWidget->revertButton()->click();

    QCOMPARE(user->records().size(), originalRecordsCount);
    QCOMPARE(user->records().front(), originalFrontRecord);

    dummyWidget->deleteLater();
}

void RevertRecordWidgetTest::test_noRevertRecord()
{
    const auto testUserDataPath = APPLICATIONFOLDER() + "\\" + id;
    makeFolder(testUserDataPath);
    QFile::copy("://UserFiles/pockets.json", testUserDataPath + "\\pockets.json");
    QFile::copy("://UserFiles/records.json", testUserDataPath + "\\records.json");

    auto user = std::make_shared<User>(username, password, id);
    const auto originalRecordsCount = user->records().size();

    const auto record = Content::Records::Record(1500, QDate::currentDate(), QTime::currentTime(), "test", "test", user->pockets().front().name());

    QWidget* dummyWidget = new QWidget();
    dummyWidget->show();

    Notification::RevertRecordWidget* revertRecordWidget = new Notification::RevertRecordWidget(record, user, dummyWidget);
    Q_UNUSED(revertRecordWidget)

    QCOMPARE(user->records().size(), originalRecordsCount + 1);
    QCOMPARE(user->records().front(), record);

    dummyWidget->deleteLater();
}
