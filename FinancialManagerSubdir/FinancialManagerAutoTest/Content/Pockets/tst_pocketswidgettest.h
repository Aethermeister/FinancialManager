#ifndef POCKETSWIDGETTEST_H
#define POCKETSWIDGETTEST_H

#include <QTest>

class PocketsWidgetTest : public QObject
{
    Q_OBJECT
public:
    PocketsWidgetTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void test_defaultUi();
    void test_newPocketFalse();
    void test_newPocketTrue();

};

#endif // POCKETSWIDGETTEST_H
