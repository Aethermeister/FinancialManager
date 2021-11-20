#ifndef CONTENTWIDGETTEST_H
#define CONTENTWIDGETTEST_H

#include <QTest>

class ContentWidgetTest : public QObject
{
    Q_OBJECT
public:
    ContentWidgetTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_contentWidgets();
};

#endif // CONTENTWIDGETTEST_H
