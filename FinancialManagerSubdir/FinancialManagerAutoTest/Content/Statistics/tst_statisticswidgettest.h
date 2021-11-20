#ifndef STATISTICSWIDGETTEST_H
#define STATISTICSWIDGETTEST_H

#include <QTest>

class StatisticsWidgetTest : public QObject
{
    Q_OBJECT
public:
    StatisticsWidgetTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_statiscticsWidgets();
};

#endif // STATISTICSWIDGETTEST_H
