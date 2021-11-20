#include "notificationwidget.h"
#include "ui_notificationwidget.h"

namespace Notification
{
    NotificationWidget::NotificationWidget(const QString& message, QWidget *parent) :
        QFrame(parent),
        NotificationBase(this, parent),
        ui(new Ui::NotificationWidget),
        m_message(message)
    {
        ui->setupUi(this);

        initializeUi();
    }

    NotificationWidget::~NotificationWidget()
    {
        delete ui;
    }

    QLabel *NotificationWidget::messageLabel()
    {
        return ui->m_message_lbl;
    }

    void NotificationWidget::initializeUi()
    {
        //Initialize the base ui
        NotificationBase::initializeUi();

        ui->m_message_lbl->setText(m_message);
    }
}
