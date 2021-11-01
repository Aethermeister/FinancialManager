#include "overviewwidget.h"
#include "ui_overviewwidget.h"
#include "Components/generaloverviewmessagewidget.h"
#include "Components/statisticsoverviewwidget.h"

namespace Content::Overview
{
    OverviewWidget::OverviewWidget(std::shared_ptr<User> user, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::OverviewWidget),
        m_user(user)
    {
        ui->setupUi(this);

        initializeUi();
    }

    OverviewWidget::~OverviewWidget()
    {
        delete ui;
    }

    void OverviewWidget::initializeUi()
    {
        //Check the user's Pocket and Records list
        //and show the general help message or the statistics overview widget depending on the result
        if(m_user->pockets().empty() || m_user->records().empty())
        {
            showGeneralOverviewMessage();
        }
        else
        {
            showStatisticsOverview();
        }
    }

    void OverviewWidget::showGeneralOverviewMessage()
    {
        //Create the GeneralOverviewMessageWidget
        Components::GeneralOverviewMessageWidget* generalOverviewMessageWidget = new Components::GeneralOverviewMessageWidget(this);
        ui->m_overviewContent_layout->addWidget(generalOverviewMessageWidget);
    }

    void OverviewWidget::showStatisticsOverview()
    {
        //Create the StatisticsOverviewWidget
        Components::StatisticsOverviewWidget* statisticsOverviewWidget = new Components::StatisticsOverviewWidget(m_user, this);
        ui->m_overviewContent_layout->addWidget(statisticsOverviewWidget);
    }
}
