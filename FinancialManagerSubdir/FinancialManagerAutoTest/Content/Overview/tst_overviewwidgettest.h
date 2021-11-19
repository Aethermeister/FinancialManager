#ifndef OVERVIEWWIDGETTEST_H
#define OVERVIEWWIDGETTEST_H

#include <QTest>

class OverviewWidgetTest : public QObject
{
    Q_OBJECT
public:
    OverviewWidgetTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void test_overviewWidgetWithNewUser();
    void test_overviewWidgetWithOldUser();

};

#endif // OVERVIEWWIDGETTEST_H
