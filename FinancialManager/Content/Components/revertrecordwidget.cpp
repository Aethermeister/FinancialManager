#include "revertrecordwidget.h"
#include "ui_revertrecordwidget.h"
#include "Core/defines.h"

#include <QTimer>
#include <QDebug>

namespace Content::Component
{
QList<RevertRecordWidget*> RevertRecordWidget::ActiveRevertRecordsWidgets{};

    RevertRecordWidget::RevertRecordWidget(const Record& record, std::shared_ptr<User> user, QWidget *parent) :
        QFrame(parent),
        ui(new Ui::RevertRecordWidget),
        m_record(record),
        m_user(user)
    {
        ui->setupUi(this);

        //Store this widget in the static QList for further usage
        ActiveRevertRecordsWidgets.append(this);
        parent->installEventFilter(this);

        initializeUi();
        initializeConnections();
    }

    RevertRecordWidget::~RevertRecordWidget()
    {
        //Remove this widget from the static QList since it won't be needed anymore
        ActiveRevertRecordsWidgets.removeOne(this);
        //Update the position of the active widgets
        //and persist the Record data
        moveActiveRevertRecordsWidgets();
        persistRecord();

        delete ui;
    }

    void RevertRecordWidget::initializeUi()
    {
        //Set the text of the amount QLabel
        const auto amount = m_record.Amount;
        auto amountString = QString::number(amount);

        //Check whether the amount value is negative or not
        //and change the style accordingly
        const bool isAmountNegative = amount < 0;
        if(!isAmountNegative)
        {
            amountString = "+" + amountString;
        }
        ui->m_amount_lbl->setText(amountString);
        setLabelNegativeState(ui->m_amount_lbl, isAmountNegative);

        //Create a QTimer to 'animate' the QProgreesBar
        //and provide time for the user to revert the changes
        m_timer = new QTimer(this);
        m_timer->setInterval(m_timeout);
        connect(m_timer, &QTimer::timeout, [=]
        {
            //Set the QProgressBar value using the original and remaining time
            ui->m_progressBar->setValue(m_remainingTime * 100 / m_time);

            //Decrease the remaining time for the elapsed time
            //and stop the timer if the counter hits 0 ehich means that the user did not reverted the changes
            m_remainingTime -= m_timeout;
            if(m_remainingTime <= 0)
            {
                m_timer->stop();
                this->deleteLater();
            }
        });

        m_timer->start();

        moveActiveRevertRecordsWidgets();
    }

    void RevertRecordWidget::initializeConnections() const
    {
        connect(ui->m_revent_btn, &QPushButton::clicked, this, &RevertRecordWidget::slot_revertButtonClicked);
    }

    bool RevertRecordWidget::eventFilter(QObject *watched, QEvent *event)
    {
        //If the event is a resize event and the whatched object is the parent widget
        //move the currently active widgets so they always keep their correct position
        if(watched == parentWidget() &&
                event->type() == QEvent::Resize)
        {
            moveActiveRevertRecordsWidgets();
        }

        return QWidget::eventFilter(watched, event);
    }

    void RevertRecordWidget::moveActiveRevertRecordsWidgets()
    {
        int positionIndex = 1;
        const int spacing = 5;

        //Move each active RevertRecordWidget to the correct position
        //Position index is used so the widgets are shown above each other
        for(auto& revertRecordWidget : ActiveRevertRecordsWidgets)
        {
            revertRecordWidget->move(parentWidget()->width() - width() - spacing,
                                     parentWidget()->height() - (positionIndex * height()) - (positionIndex * spacing));
            positionIndex += 1;
        }
    }

    void RevertRecordWidget::persistRecord()
    {
        //If the revert button was not clicked previously store the new Record through the User
        if(!m_isRevertClicked)
        {
            m_user->persistNewRecord(std::move(m_record));
        }
    }

    void RevertRecordWidget::slot_revertButtonClicked()
    {
        //Set the revert flag and stop the countdown
        m_isRevertClicked = true;
        m_timer->stop();
        this->deleteLater();
    }
}
