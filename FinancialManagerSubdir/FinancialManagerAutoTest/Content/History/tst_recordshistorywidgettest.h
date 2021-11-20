#ifndef RECORDSHISTORYWIDGETTEST_H
#define RECORDSHISTORYWIDGETTEST_H

#include <QTest>

class RecordsHistoryWidgetTest : public QObject
{
    Q_OBJECT
public:
    RecordsHistoryWidgetTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void test_defaultUi();
    void test_deleteRecord();
    void test_filterHistoryList();
};

#endif // RECORDSHISTORYWIDGETTEST_H
