#include "tst_notificationwidgettest.h"
#include "Notification/notificationwidget.h"

void NotificationWidgetTest::test_notificationText()
{
    QWidget* dummyWidget = new QWidget();
    dummyWidget->show();

    const QString notificationText = "Test";
    Notification::NotificationWidget* notificationWidget = new Notification::NotificationWidget(notificationText, dummyWidget);

    QCOMPARE(notificationWidget->messageLabel()->text(), notificationText);

    dummyWidget->deleteLater();
}
