#include "tst_statisticswidgettest.h"
#include "TestUtils.h"
#include "Core/defines.h"
#include "Content/Statistics/statisticswidget.h"
#include "Content/Statistics/Components/cashflowchartview.h"
#include "Content/Statistics/Components/pocketsvaluechartview.h"
#include "Content/Statistics/Components/recordsdatachartview.h"

void StatisticsWidgetTest::initTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
    makeFolder(APPLICATIONFOLDER());
}

void StatisticsWidgetTest::cleanupTestCase()
{
    deleteFile(USERSFILE);
    deleteFolder(APPLICATIONFOLDER());
}

void StatisticsWidgetTest::test_statiscticsWidgets()
{
    const auto testUserDataPath = APPLICATIONFOLDER() + "\\" + id;
    makeFolder(testUserDataPath);
    QFile::copy("://UserFiles/pockets.json", testUserDataPath + "\\pockets.json");
    QFile::copy("://UserFiles/records.json", testUserDataPath + "\\records.json");

    auto user = std::make_shared<User>(username, password, id);
    Content::Statistics::StatisticsWidget* statisticsWidget = new Content::Statistics::StatisticsWidget(user);
    statisticsWidget->show();

    auto statisticsSelectionWidget = statisticsWidget->findChild<Content::Statistics::StatisticsSelectionWidget*>();
    QVERIFY(statisticsSelectionWidget);

    statisticsSelectionWidget->cashFlowButton()->click();
    QVERIFY(statisticsWidget->findChild<Content::Statistics::Components::CashFlowChartView*>());

    statisticsWidget->backButton()->click();
    auto statisticsSelectionWidget2 = statisticsWidget->findChild<Content::Statistics::StatisticsSelectionWidget*>();
    QVERIFY(statisticsSelectionWidget2);

    statisticsSelectionWidget2->pocketValueAndUsageButton()->click();
    QVERIFY(statisticsWidget->findChild<Content::Statistics::Components::PocketsValueChartView*>());

    statisticsWidget->backButton()->click();
    auto statisticsSelectionWidget3 = statisticsWidget->findChild<Content::Statistics::StatisticsSelectionWidget*>();
    QVERIFY(statisticsSelectionWidget3);

    statisticsSelectionWidget3->recordsDataButton()->click();
    QVERIFY(statisticsWidget->findChild<Content::Statistics::Components::RecordsDataChartView*>());


    statisticsWidget->deleteLater();
}
