#ifndef CASHFLOWCHARTVIEW_H
#define CASHFLOWCHARTVIEW_H

#include "chartviewbase.h"

#include <unordered_map>

namespace Content::Statistics::Components
{
    /**
     * Enum which holds data for the time range the chart uses
     *
     * WEEK: Show the last 7 days
     * MONTH: Show the last 1 month
     * YEAR: Show the last 1 year
     * FULL: Fit the range to the first pocket creation date
    */
    enum CashFlowInterval
    {
        WEEK,
        MONTH,
        YEAR,
        FULL,

        END_OF_ENUM
    };

    /**
     * Ui class which shows the Pockets value change over time
     * With additional options the user can visualize a filtered display
    */
    class CashFlowChartView : public ChartViewBase
    {
        Q_OBJECT
    public:
        CashFlowChartView(std::shared_ptr<User> user, QWidget* parent = Q_NULLPTR);
        ~CashFlowChartView();

        /**
         * Creates the corresponding series for the Pocket value change over time
        */
        virtual void initializeSeries() override;
        /**
         * Creates the chart modifier widgets
        */
        virtual void initializeChartAdjustingWidgets() override;

    protected:
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

    private:
        /**
         * Converts the parameter given CashFlowInterval enum value to a QString representation
        */
        static QString convertCashFlowIntervalToString(const CashFlowInterval& interval);

        /**
         * Collects and stores the necessary Pocket and Record data for the series creation
        */
        void collectRecordsSeriesData();

        /**
         * Creates and returns a QPushButton
         * A QMenu is attached to this button with QActions
         * The actions are used to change the chart date axis range
        */
        QPushButton* createIntervalButton();

        /**
         * Creates and returns a QPushButton
         * A QMenu is attached to this button
         * which lists the Pockets and provides filtering option for them
        */
        QPushButton* createPocketFilterButton();

        /**
         * Creates the base of the chart X and Y axis
         * and attaches them to the chart and the series in teh chart
        */
        void createChartAxes();
        /**
         * Updates the axis range and properties according to the selected interval and filter
        */
        void updateChartAxes();
        /**
         * Sets the visibility of each series according to the filter list
        */
        void filterSeries();

        /**
         * Returns the creation date of the oldest Pocket
         * The filter list is taken into account
        */
        QDateTime filteredFirstDate() const;
        /**
         * Returns the min and max values of the series
         * between now and the parameter given date range
         * The filter list is taken into account
        */
        std::pair<int,int> filteredMinMaxValues(QDateTime minDateTime) const;

        /**
         * Date axis interval
         * The last 7 days is displayed as default
        */
        CashFlowInterval m_interval = CashFlowInterval::WEEK;

        /**
         * The date (X) axis of the chart and its series
        */
        QDateTimeAxis* m_dateAxis;
        /**
         * The value (Y) axis of the chart and its series
        */
        QValueAxis* m_valueAxis;

        /**
         * Summarized Pocket value state for each day since the day of the Pocket creation
        */
        std::unordered_map<QString, std::vector<std::pair<QDate, int>>> m_pocketCashFlowMap;
        /**
         * The series of the chart mapped to their Pocket
        */
        std::unordered_map<QString, QLineSeries*> m_pocketSeries;

        /**
         * Stringlist which contains the name of Pockets which has to be filtered
         * As default this list is empty
        */
        QStringList m_pocketFilter;
    };
}

#endif // CASHFLOWCHARTVIEW_H
