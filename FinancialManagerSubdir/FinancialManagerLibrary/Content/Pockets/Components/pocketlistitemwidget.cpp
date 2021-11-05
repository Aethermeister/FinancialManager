#include "pocketlistitemwidget.h"
#include "ui_pocketlistitemwidget.h"
#include "Core/widgetdefines.h"
#include "pocketdeletiondialog.h"
#include "Notification/notificationwidget.h"

#include <QPixmap>

#include <Content/contentwidget.h>

namespace Content::Pockets::Component
{
    PocketListItemWidget::PocketListItemWidget(std::shared_ptr<User> user, const Pocket &pocket, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::PocketListItemWidget),
        m_user(user),
        m_pocket(pocket)
    {
        ui->setupUi(this);

        initializeUi();
        initializeConnections();
    }

    PocketListItemWidget::~PocketListItemWidget()
    {
        delete ui;
    }

    void PocketListItemWidget::initializeUi()
    {
        //Attribute has to be set so the stylesheet is applied to the custom widget
        setAttribute(Qt::WA_StyledBackground);

        //Set the correct type indicator image according to the set PocketType
        QPixmap pixmap = QPixmap();
        if(m_pocket.type() == Content::Pockets::PocketType::CASH)
        {
            pixmap.load("://Images/cash.png");
        }
        else if(m_pocket.type() == Content::Pockets::PocketType::CARD)
        {
            pixmap.load("://Images/card.png");
        }
        ui->m_pocketImage_lbl->setPixmap(pixmap);

        //Set the name and value of the Pocket list item
        ui->m_pocketName_lbl->setText(m_pocket.name());
        setLabelNegativeState(ui->m_value_lbl, m_pocket.value());
        setLabelNegativeState(ui->m_initialValue_lbl, m_pocket.initialValue());

        //Create a QString which indicates the records count linked to the given Pocket
        const QString recordsCountInformation = QString("%0 record(s)").arg(m_pocket.recordsCount());
        ui->m_recordsCount_lbl->setText(recordsCountInformation);

        //Get the date when the Pocket was last used
        const auto& lastUsedDate = m_pocket.lastUsedDate();
        ui->m_lastUsageDate_lbl->setVisible(lastUsedDate.isValid());
        //If the retrieved QDate is valid (the Pocket already has Record(s)) calculate the elapsed days
        if(lastUsedDate.isValid())
        {
            //Get the Julian day of the current date and calculate the difference between the current and last usage date
            const auto currentJulianDay = QDate::currentDate().toJulianDay();
            const auto julianDaysDifference = currentJulianDay - lastUsedDate.toJulianDay();

            //Create a QString which indicates when was the Pocket used last time
            const QString lastUsedInformation = QString("Last used %0 day(s) ago, %1")
                    .arg(julianDaysDifference).arg(lastUsedDate.toString("yyyy.MM.dd, dddd"));
            ui->m_lastUsageDate_lbl->setText(lastUsedInformation);
        }

        //Show the creation date of the Pocket
        ui->m_creationDate_lbl->setText(m_pocket.creationDate().toString("yyyy.MM.dd."));
    }

    void PocketListItemWidget::initializeConnections()
    {
        //Connect lambda to the delete QPushButton click signal
        connect(ui->m_deletePocket_btn, &QPushButton::clicked, [=]
        {
            //Show a warning dialog before deleting the Pocket
            PocketDeletionDialog* deletionWidget = new PocketDeletionDialog(m_pocket.name(), m_pocket.recordsCount());

            //Connect lambda to the deletion warning dialog's sig_finish signal
            //This signal's parameter indicates whether the user confirmed the deletion or canceled it
            connect(deletionWidget, &PocketDeletionDialog::sig_finished, [=](DeletionResult result)
            {
                //If the user confirmed the deletion of the Pocket than
                //Delete the Pocket from the users' list
                //Show notification which indicates the deletion of the Pocket
                //Delete this object so the Pocket list is updated
                if(result == DeletionResult::DELETE)
                {
                    m_user->deletePocket(m_pocket);

                    const auto notificationMessage = QString("The pocket %0 with %1 record(s) has been deleted").arg(m_pocket.name()).arg(m_pocket.recordsCount());
                    Notification::NotificationWidget* pocketDeletedNotification = new Notification::NotificationWidget(notificationMessage, Content::ContentWidget::instance());
                    pocketDeletedNotification->show();

                    deleteLater();
                }
            });

            //Show the warning dialog
            deletionWidget->exec();
        });
    }
}
