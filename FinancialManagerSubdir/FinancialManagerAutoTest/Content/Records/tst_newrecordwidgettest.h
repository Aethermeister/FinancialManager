#ifndef NEWRECORDWIDGETTEST_H
#define NEWRECORDWIDGETTEST_H

#include <QTest>

class NewRecordWidgetTest : public QObject
{
    Q_OBJECT
public:
    NewRecordWidgetTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void test_defaultUi();
    void test_createNewRecord();
};

#endif // NEWRECORDWIDGETTEST_H
