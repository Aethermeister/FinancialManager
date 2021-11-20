#ifndef NOTIFICATIONWIDGETTEST_H
#define NOTIFICATIONWIDGETTEST_H

#include <QTest>

class NotificationWidgetTest : public QObject
{
    Q_OBJECT
public:
    NotificationWidgetTest() = default;

private slots:
    void test_notificationText();
};

#endif // NOTIFICATIONWIDGETTEST_H
