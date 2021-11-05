#include "notificationbase.h"

namespace Notification
{
    QList<QWidget*> NotificationBase::ActiveNotificationWidgets{};

    NotificationBase::NotificationBase(QWidget *notificationWidget, QWidget* parentWidget) :
        m_notificationWidget(notificationWidget),
        m_parentWidget(parentWidget)
    {
        ActiveNotificationWidgets.append(m_notificationWidget);
    }

    NotificationBase::~NotificationBase()
    {
        m_timer->stop();

        ActiveNotificationWidgets.removeOne(m_notificationWidget);

        //Update the position of the active widgets
        moveActiveNotificationWidgets();
    }

    void NotificationBase::initializeUi()
    {
        m_notificationWidget->setFixedSize(250, 125);

        //Create a QTimer to show the notification QWidget for a short time
        m_timer = new QTimer(m_notificationWidget);
        m_timer->setInterval(m_timeout);
        m_notificationWidget->connect(m_timer, &QTimer::timeout, [=]
        {
            //Decrease the remaining time for the elapsed time
            //and stop the timer if the counter hits 0 ehich means that the user did not reverted the changes
            m_remainingTime -= m_timeout;
            if(m_remainingTime <= 0)
            {
                m_timer->stop();
                m_notificationWidget->deleteLater();
            }
        });

        m_timer->start();

        moveActiveNotificationWidgets();
    }

    void NotificationBase::moveActiveNotificationWidgets()
    {
        int positionIndex = 1;
        const int spacing = 5;

        //Move each active notification widgets to the correct position
        //Position index is used so the widgets are shown above each other
        for(auto& notificationWidget : ActiveNotificationWidgets)
        {
            notificationWidget->move(notificationWidget->parentWidget()->width() - notificationWidget->width() - spacing,
                                     notificationWidget->parentWidget()->height() - (positionIndex * notificationWidget->height()) - (positionIndex * spacing));
            positionIndex += 1;
        }
    }

}
