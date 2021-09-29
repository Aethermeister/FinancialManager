#include "revertrecordwidget.h"
#include "ui_revertrecordwidget.h"
#include "Core/defines.h"

namespace Notification
{
    RevertRecordWidget::RevertRecordWidget(const Record& record, std::shared_ptr<User> user, QWidget *parent) :
        QFrame(parent),
        NotificationBase(this, parent),
        ui(new Ui::RevertRecordWidget),
        m_record(record),
        m_user(user)
    {
        ui->setupUi(this);

        //Save the new Record
        m_user->persistNewRecord(m_record);

        initializeUi();
        initializeConnections();
    }

    RevertRecordWidget::~RevertRecordWidget()
    {
        delete ui;
    }

    void RevertRecordWidget::initializeUi()
    {
        //Initialize the base ui
        NotificationBase::initializeUi();

        //Set the text of the amount QLabel
        setLabelNegativeState(ui->m_amount_lbl, m_record.Amount);

        connect(m_timer, &QTimer::timeout, [=]
        {
            //Set the QProgressBar value using the original and remaining time
            ui->m_progressBar->setValue(m_remainingTime * 100 / m_time);
        });
    }

    void RevertRecordWidget::initializeConnections() const
    {
        connect(ui->m_revent_btn, &QPushButton::clicked, this, &RevertRecordWidget::slot_revertButtonClicked);
    }

    void RevertRecordWidget::slot_revertButtonClicked()
    {
        //Delete the Record through the User
        m_user->deleteRecord(m_record);
        this->deleteLater();
    }
}
