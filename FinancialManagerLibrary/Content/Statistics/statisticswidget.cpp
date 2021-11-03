#include "statisticswidget.h"
#include "ui_statisticswidget.h"
#include "Core/widgetdefines.h"
#include "Components/cashflowchartview.h"
#include "Components/pocketsvaluechartview.h"
#include "Components/recordsdatachartview.h"

namespace Content::Statistics
{
    StatisticsWidget::StatisticsWidget(std::shared_ptr<User> user, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::StatisticsWidget),
        m_user(user)
    {
        ui->setupUi(this);

        initializeUi();
        initializeConnections();
    }

    StatisticsWidget::~StatisticsWidget()
    {
        //Delete the current ChartViewBase widget from the content area
        deleteActiveContentWidget<Components::ChartViewBase*>(this, ui->m_statisticsContainer_layout);
        delete ui;
    }

    void StatisticsWidget::initializeUi()
    {
        //Always show the selection widget when the statistics widget is first shown
        showStatisticsSelectionWidget();
    }

    void StatisticsWidget::initializeConnections() const
    {
        connect(ui->m_back_btn, &QPushButton::clicked, this, &StatisticsWidget::showStatisticsSelectionWidget);
    }

    void StatisticsWidget::showStatisticsSelectionWidget()
    {
        //Delete the current ChartViewBase widget from the content area
        deleteActiveContentWidget<Components::ChartViewBase*>(this, ui->m_statisticsContainer_layout);

        //Do not show the Back button if the selection widget is visible
        ui->m_back_btn->setVisible(false);

        //Create a new StatisticsSelectionWidget and add it to the content area
        StatisticsSelectionWidget* statisticsSelectionWidget = new StatisticsSelectionWidget(this);
        ui->m_statisticsContainer_layout->addWidget(statisticsSelectionWidget);

        connect(statisticsSelectionWidget, &StatisticsSelectionWidget::sig_statisticsTypeSelected, this, &StatisticsWidget::slot_showSelectedStatisticsWidget);
    }

    void StatisticsWidget::showCashFlowStatisticsWidget()
    {
        //Create the Cash Flow chart widget
        Components::CashFlowChartView* cashFlowChartView = new Components::CashFlowChartView(m_user, this);
        initializeSelectedStatisticsWidget(cashFlowChartView);
    }

    void StatisticsWidget::showPocketValueAndUsageStatisticsWidget()
    {
        //Create the Pocket value and usage chart widget
        Components::PocketsValueChartView* pocketsValueChartView = new Components::PocketsValueChartView(m_user, this);
        initializeSelectedStatisticsWidget(pocketsValueChartView);
    }

    void StatisticsWidget::showRecordsDataStatisticsWidget()
    {
        //Create the Records data chart widget
        Components::RecordsDataChartView* recordsDataChartView = new Components::RecordsDataChartView(m_user, this);
        initializeSelectedStatisticsWidget(recordsDataChartView);
    }

    void StatisticsWidget::initializeSelectedStatisticsWidget(Components::ChartViewBase *selectedChartView)
    {
        //Initialize the series and modifier widgets of teh parameter given chart view
        //And show the chart view in the content area
        selectedChartView->initializeSeries();
        selectedChartView->initializeChartAdjustingWidgets();

        ui->m_statisticsContainer_layout->addWidget(selectedChartView);

        //Insert the chart widget related modifier widgets in the header layout next to the Back button
        //The start position is 2 because of the Back button and separator spacer
        int positionCounter = 2;
        const auto& chartAdjustingWidgets = selectedChartView->chartAdjustingWidgets();
        for(const auto widget : chartAdjustingWidgets)
        {
            ui->m_chartHeader_layout->insertWidget(positionCounter, widget);
        }
    }

    void StatisticsWidget::slot_showSelectedStatisticsWidget(Content::Statistics::StatisticsType type)
    {
        //Delete the current StatisticsSelectionWidget widget from the content area
        deleteActiveContentWidget<StatisticsSelectionWidget*>(this, ui->m_statisticsContainer_layout);

        //According to the parameter given type show the needed statistics widget
        if(type == StatisticsType::CASH_FLOW)
        {
            showCashFlowStatisticsWidget();
        }
        else if(type == StatisticsType::POCKET_VALUE_AND_USAGE)
        {
            showPocketValueAndUsageStatisticsWidget();
        }
        else if(type == StatisticsType::RECORDS_DATA)
        {
            showRecordsDataStatisticsWidget();
        }

        //Show the Back button when a chart widget is shown in the content area
        ui->m_back_btn->setVisible(true);
    }
}
