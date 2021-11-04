#ifndef NOTIFICATIONBASE_H
#define NOTIFICATIONBASE_H

#include <QWidget>
#include <QTimer>

namespace Notification
{
    /**
     * Base class of the notification ui classes
    */
    class NotificationBase
    {
    public:
        NotificationBase(QWidget* notificationWidget, QWidget* parentWidget);
        ~NotificationBase();

        /**
         * Move the currently active notification widgets
         * so they are shown in their correct position
        */
        static void moveActiveNotificationWidgets();

        /**
         * Stores the currently active RevertRecordWidget widgets
        */
        static QList<QWidget*> ActiveNotificationWidgets;

    protected:

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();

        /**
         * QTimer which is used to time the disappearance of the notification
        */
        QTimer* m_timer;
        /**
         * The interval for the QTimer timeout signal
        */
        const int m_timeout = 50;
        /**
         * The QTimer runs for this long [ms]
        */
        const int m_time = 5000;
        /**
         * The QTimer has this long to run [ms]
        */
        int m_remainingTime = m_time;

    private:
        /**
         * The actual, visible notification QWidget
        */
        QWidget* m_notificationWidget;
        /**
         * Parent QWidget of the m_notificationWidget
        */
        QWidget* m_parentWidget;
    };
}

#endif // NOTIFICATIONBASE_H
