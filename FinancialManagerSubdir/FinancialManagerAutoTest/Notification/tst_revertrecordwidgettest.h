#ifndef REVERTRECORDWIDGETTEST_H
#define REVERTRECORDWIDGETTEST_H

#include <QTest>

class RevertRecordWidgetTest : public QObject
{
    Q_OBJECT
public:
    RevertRecordWidgetTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void test_revertRecord();
    void test_noRevertRecord();
};

#endif // REVERTRECORDWIDGETTEST_H
