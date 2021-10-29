#include "statisticswidget.h"
#include "ui_statisticswidget.h"
#include "Core/widgetdefines.h"
#include "Components/pocketsvaluechartview.h"

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

    void StatisticsWidget::showPocketValueStatisticsWidget()
    {
        //Create the Pocket value and usage chart widget
        Components::PocketsValueChartView* pocketsValueChartView = new Components::PocketsValueChartView(m_user, this);
        pocketsValueChartView->initializeSeries(); //Initialize the value and usage charts externally
        pocketsValueChartView->initializeChartAdjustingWidgets(); //Initialize the corresponding modifier widgets
        ui->m_statisticsContainer_layout->addWidget(pocketsValueChartView);

        //Insert the chart widget related modifier widgets in the header layout next to the Back button
        //The start position is 2 because of the Back button and separator spacer
        int positionCounter = 2;
        const auto& chartAdjustingWidgets = pocketsValueChartView->chartAdjustingWidgets();
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
        if(type == StatisticsType::POCKET_VALUE_AND_USAGE)
        {
            showPocketValueStatisticsWidget();
        }

        //Show the Back button when a chart widget is shown in the content area
        ui->m_back_btn->setVisible(true);
    }
}
