#include "chartviewbase.h"

namespace Content::Statistics::Components
{
    ChartViewBase::ChartViewBase(std::shared_ptr<User> user, QWidget *parent) : QChartView(parent), m_user(user)
    {
        initializeChartBase();
    }

    ChartViewBase::~ChartViewBase()
    {
        //Free memory
        deleteAdjustingWidgets();
        deleteChartSeries();
    }

    std::vector<QWidget *> &ChartViewBase::chartAdjustingWidgets()
    {
        return m_chartAdjustingWidgets;
    }

    void ChartViewBase::deleteAdjustingWidgets()
    {
        //Delete the chart modifier widgets
        for(auto widget : m_chartAdjustingWidgets)
        {
            widget->deleteLater();
        }
        m_chartAdjustingWidgets.clear();
        m_chartAdjustingWidgets.shrink_to_fit();
    }

    void ChartViewBase::deleteChartSeries()
    {
        //Delete the collected series
        for(auto series : m_chartSeries)
        {
            series->deleteLater();
        }
        m_chartSeries.clear();
        m_chartSeries.shrink_to_fit();
    }

    void ChartViewBase::initializeChartBase()
    {
        //Create a chart object and set its ui related properties
        m_chart = new QChart();
        m_chart->setTheme(QChart::ChartThemeDark);
        m_chart->setBackgroundRoundness(0);
        m_chart->setBackgroundVisible(false);

        auto chartFont = m_chart->titleFont();
        chartFont.setBold(true);
        chartFont.setPointSize(18);
        m_chart->setTitleFont(chartFont);

        m_chart->legend()->hide();

        setChart(m_chart);
        setRenderHint(QPainter::Antialiasing);
    }
}
