#ifndef CHARTVIEWBASE_H
#define CHARTVIEWBASE_H
#include "user.h"

#include <QtCharts>

namespace Content::Statistics::Components
{
    /**
     * Base class of the statistics chart Ui classes
    */
    class ChartViewBase : public QChartView
    {
        Q_OBJECT
    public:
        explicit ChartViewBase(std::shared_ptr<User> user, QWidget* parent = Q_NULLPTR);
        virtual ~ChartViewBase();

        /**
         * Pure virtual function of series initialization
        */
        virtual void initializeSeries() = 0;
        /**
         * Pure virtual function of chart modifier widget initialization
        */
        virtual void initializeChartAdjustingWidgets() = 0;

        /**
         * Returns the reference to the list of chart modifier widgets
        */
        std::vector<QWidget*>& chartAdjustingWidgets();

    protected:
        /**
         * The current user
        */
        std::shared_ptr<User> m_user;
        /**
         * The chart widget the actual data is visualized in
        */
        QChart* m_chart;
        /**
         * List of the chart modifier widgets
        */
        std::vector<QWidget*> m_chartAdjustingWidgets;
        /**
         * List of the chart series
        */
        std::vector<QAbstractSeries*> m_chartSeries;

    private:
        /**
         * Initializes the base state of the QChart
        */
        void initializeChartBase();
        /**
         * Deletes the collected chart modifier widgets
        */
        void deleteAdjustingWidgets();
        /**
         * Deletes the collected series
        */
        void deleteChartSeries();
    };
}

#endif // CHARTVIEWBASE_H
