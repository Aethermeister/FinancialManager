#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include "notificationbase.h"

#include <QFrame>
#include <QLabel>

namespace Ui {
class NotificationWidget;
}

namespace Notification
{
    /**
     * Component ui class derived from the NotificationBase class
     * This class is responsible to show actual information
    */
    class LIB_EXPORT NotificationWidget : public QFrame, public NotificationBase
    {
        Q_OBJECT

    public:
        explicit NotificationWidget(const QString& message, QWidget *parent = nullptr);
        ~NotificationWidget();

        /**
         * Returns the notification widget's message QQLabel
         * Used so test project(s) can access it
        */
        QLabel* messageLabel();

    private:
        Ui::NotificationWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();

        /**
         * The message which needs to be displayed in the notification widget
        */
        QString m_message;
    };
}
#endif // NOTIFICATIONWIDGET_H
