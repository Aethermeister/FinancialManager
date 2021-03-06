#include "contentwidget.h"
#include "ui_contentwidget.h"
#include "Core/defines.h"
#include "Overview/overviewwidget.h"
#include "Pockets/pocketswidget.h"
#include "Records/newrecordwidget.h"
#include "History/recordshistorywidget.h"
#include "Statistics/statisticswidget.h"
#include "profilewidget.h"
#include "Notification/notificationbase.h"

namespace Content
{
    ContentWidget::ContentWidget(std::shared_ptr<User> user, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ContentWidget),
        m_user(std::move(user))
    {
        ui->setupUi(this);

        //Set the instance so it points to 'this' object
        s_instance = this;

        //Set the initial state of the widget
        initializeConnections();
        showOverviewWidget();
    }

    ContentWidget::~ContentWidget()
    {
        delete ui;
    }

    ContentWidget *ContentWidget::s_instance = nullptr;

    ContentWidget *ContentWidget::instance()
    {
        return s_instance;
    }

    QPushButton *ContentWidget::overviewButton()
    {
        return ui->m_overview_btn;
    }

    QPushButton *ContentWidget::pocketsButton()
    {
        return ui->m_pockets_btn;
    }

    QPushButton *ContentWidget::newRecordButton()
    {
        return ui->m_newRecord_btn;
    }

    QPushButton *ContentWidget::historyButton()
    {
        return ui->m_history_btn;
    }

    QPushButton *ContentWidget::statisticsButton()
    {
        return ui->m_statistics_btn;
    }

    void ContentWidget::slot_showProfileWidget()
    {
        showProfileWidget();
    }

    void ContentWidget::resizeEvent(QResizeEvent *event)
    {
        Q_UNUSED(event);

        Notification::NotificationBase::moveActiveNotificationWidgets();
    }

    void ContentWidget::initializeConnections() const
    {
        connect(ui->m_overview_btn, &QPushButton::clicked, this, &ContentWidget::showOverviewWidget);
        connect(ui->m_pockets_btn, &QPushButton::clicked, this, &ContentWidget::showPocketsWidget);
        connect(ui->m_newRecord_btn, &QPushButton::clicked, this, &ContentWidget::showNewRecordWidget);
        connect(ui->m_history_btn, &QPushButton::clicked, this, &ContentWidget::showHistoryWidget);
        connect(ui->m_statistics_btn, &QPushButton::clicked, this, &ContentWidget::showStatisticsWidget);

        connect(ui->m_exit_btn, &QPushButton::clicked, &QApplication::quit);
    }

    void ContentWidget::adjustControlButtons()
    {
        //Since the control buttons in the control menu area can be 'clicked' by code they cannot be exclusive
        //Therefore setting the correct checked state for each button has to be done by code

        //Get the sender QPushButton
        //This method is not connected to any QPushButton directly but is called from such methods
        const auto senderButton = qobject_cast<QPushButton*>(sender());
        //Get the control QPushButtons in the control menu area
        //and set the previously checked QPushButton unchecked
        const auto controlButtons = ui->m_controlMenu_widget->findChildren<QPushButton*>();
        for(const auto& button : controlButtons)
        {
            //If the button is checked and the button is not the newly checked button furthermore the sender QPushButton is a valid button
            //set the current button to unchecked
            if(button->isChecked() && button != sender() && senderButton != nullptr)
            {
                button->setChecked(false);
                break;
            }
        }

        //If the sender QPushButton is valid set it checked
        if(senderButton)
        {
            senderButton->setChecked(true);
        }
    }

    void ContentWidget::showOverviewWidget()
    {
        adjustControlButtons();

        //Delete the current widget from the container widget
        deleteActiveContentWidget<QWidget*>(ui->m_container_widget, ui->m_container_layout);

        //Create a new OverviewWidget and add it to the container widget
        Overview::OverviewWidget* overviewWidget = new Overview::OverviewWidget(m_user, ui->m_container_widget);
        ui->m_container_layout->addWidget(overviewWidget);
    }

    void ContentWidget::showPocketsWidget()
    {
        adjustControlButtons();

        //Delete the current widget from the container widget
        deleteActiveContentWidget<QWidget*>(ui->m_container_widget, ui->m_container_layout);

        //Create a new PocketsWidget and add it to the container widget
        Pockets::PocketsWidget* pocketWidget = new Pockets::PocketsWidget(m_user, ui->m_container_widget);
        ui->m_container_layout->addWidget(pocketWidget);
    }

    void ContentWidget::showNewRecordWidget()
    {
        adjustControlButtons();

        //Delete the current widget from the container widget
        deleteActiveContentWidget<QWidget*>(ui->m_container_widget, ui->m_container_layout);

        //Create a new NewRecordWidget and add it to the container widget
        Records::NewRecordWidget* newRecordWidget = new Records::NewRecordWidget(m_user, ui->m_container_widget);
        ui->m_container_layout->addWidget(newRecordWidget);
    }

    void ContentWidget::showHistoryWidget()
    {
        adjustControlButtons();

        //Delete the current widget from the container widget
        deleteActiveContentWidget<QWidget*>(ui->m_container_widget, ui->m_container_layout);

        //Create a new RecordsHistoryWidget and add it to the container widget
        History::RecordsHistoryWidget* historyWidget = new History::RecordsHistoryWidget(m_user, ui->m_container_widget);
        ui->m_container_layout->addWidget(historyWidget);
    }

    void ContentWidget::showStatisticsWidget()
    {
        adjustControlButtons();

        //Delete the current widget from the container widget
        deleteActiveContentWidget<QWidget*>(ui->m_container_widget, ui->m_container_layout);

        //Create a new StatisticsWidget and add it to the container widget
        Statistics::StatisticsWidget* statisticsWidget = new Statistics::StatisticsWidget(m_user, ui->m_container_widget);
        ui->m_container_layout->addWidget(statisticsWidget);
    }

    void ContentWidget::showProfileWidget()
    {
        adjustControlButtons();

        //Delete the current widget from the container widget
        deleteActiveContentWidget<QWidget*>(ui->m_container_widget, ui->m_container_layout);

        //Create a new ProfileWidget and add it to the container widget
        ProfileWidget* profileWidget = new ProfileWidget(m_user, ui->m_container_widget);
        ui->m_container_layout->addWidget(profileWidget);

        connect(profileWidget, &ProfileWidget::sig_requestLogout, this, &ContentWidget::sig_logout);
    }
}
