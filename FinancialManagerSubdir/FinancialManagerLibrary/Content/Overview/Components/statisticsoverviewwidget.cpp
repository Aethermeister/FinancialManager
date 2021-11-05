#include "statisticsoverviewwidget.h"
#include "ui_statisticsoverviewwidget.h"
#include "Content/Statistics/Components/cashflowchartview.h"
#include "Content/Statistics/Components/pocketsvaluechartview.h"

namespace Content::Overview::Components
{
    StatisticsOverviewWidget::StatisticsOverviewWidget(std::shared_ptr<User> user, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::StatisticsOverviewWidget),
        m_user(user)
    {
        ui->setupUi(this);

        initializeUi();
    }

    StatisticsOverviewWidget::~StatisticsOverviewWidget()
    {
        delete ui;
    }

    void StatisticsOverviewWidget::initializeUi()
    {
        //Show a base CashFlowChartView chart
        Statistics::Components::CashFlowChartView* cashFlowChartView = new Statistics::Components::CashFlowChartView(m_user, this);
        cashFlowChartView->initializeSeries();
        ui->m_cashFlowChartView_layout->addWidget(cashFlowChartView);

        //Show a base PocketsValueChartView chart
        Statistics::Components::PocketsValueChartView* pocketsValueChartView = new Statistics::Components::PocketsValueChartView(m_user, this);
        pocketsValueChartView->initializeSeries();
        ui->m_pocketsValueChartView_layout->addWidget(pocketsValueChartView);

        //Initialize the Records history so it lists the recent Records
        ui->m_historyListing_widget->initialize(m_user);
    }
}
