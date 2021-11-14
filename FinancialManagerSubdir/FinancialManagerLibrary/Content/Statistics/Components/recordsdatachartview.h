#ifndef RECORDSDATACHARTVIEW_H
#define RECORDSDATACHARTVIEW_H

#include "chartviewbase.h"

#include <unordered_map>

namespace Content::Statistics::Components
{
    /**
     * Enum which holds values to change the displayed chart
     *
     * RECORDS_VALUE: Display the summarized records value of given item or location
     * RECORDS_COUNT: Display the summarized records count of given item or location
    */
    enum RecordsDataDisplayMode
    {
        RECORDS_VALUE,
        RECORDS_COUNT
    };

    /**
     * Enum which holds values to change the type of the displayed chart
     *
     * ITEM: Display the items of the Records
     * RECORDS_COUNT: Display the locations of the Records
    */
    enum RecordsDataDisplayType
    {
        ITEM,
        LOCATION
    };

    /**
     * Ui class which provides summarized information for Record values at locations and of items
    */
    class RecordsDataChartView : public ChartViewBase
    {
        Q_OBJECT
    public:
        RecordsDataChartView(std::shared_ptr<User> user, QWidget *parent = Q_NULLPTR);
        ~RecordsDataChartView();

        /**
         * Creates the corresponding series for the Records data
        */
        virtual void initializeSeries() override;
        /**
         * Creates the chart modifier widgets
        */
        virtual void initializeChartAdjustingWidgets() override;

    private:
        /**
         * Show the series with the needed QBarSets according to the currently set type and filter
        */
        void showSelectedBarSeries();

        /**
         * Calculate and return a QColor according to the parameter given values
        */
        QColor calculateColor(int& counter, bool isPositive);

        /**
         * Creates a menu which lists the Pockets and provides filtering option for them
        */
        QPushButton* createPocketFilterButton();

        /**
         * Creates a button which allows the user to ignore extreme positive and negative valus according to the chart average
        */
        QPushButton* createIgnoreExtremesButton();

        /**
         * Creates an indicator QLabel for the hovered QBarSets
         * This QLabel shows the name and value of a hovered QBarSet
        */
        QLabel* createBarSetValueIndicatorLabel();

        /**
         * Creates a modifier widget so the user can change the chart's display mode
        */
        QWidget* createRecordsDisplayModeModifierWidgets() const;
        /**
         * Creates a modifier widget so the user can change the chart's display type
        */
        QWidget* createRecordsDisplayTypeModifierWidgets() const;

        /**
         * Reads the Records and sorts them into maps according to specific criterias
        */
        void collectRecordsData();
        /**
         * Changes the displayed title of the axes and chart according to the selected type
        */
        void adjustSeriesDisplay();

        /**
         * Remove the extreme QBarSets from the series
        */
        void ignoreExtremeBars();

        /**
         * Creates and return one summarized list according to the currently set display mode/type and filter
        */
        const std::vector<std::pair<QString, int>> summarizeRecordsData();

        /**
         * Creates a sorted pair vector from the parameter given map and returns it via the parameter given vector
        */
        void sortSummarizedRecordsData(const std::unordered_map<QString, int>& summarizedRecordsData, std::vector<std::pair<QString, int>>& sortedRecordsData);

        /**
         * Returns which previously collected and stored map should be processed for the chart
        */
        std::unordered_map<QString, std::unordered_map<QString, int>>& selectedRecordsData();

        /**
         * Record values mapped to items which is mapped to Pocket
        */
        std::unordered_map<QString, std::unordered_map<QString, int>> m_recordsItemsValueMap;
        /**
         * Record count mapped to items which is mapped to Pocket
        */
        std::unordered_map<QString, std::unordered_map<QString, int>> m_recordsItemsCountMap;

        /**
         * Record values mapped to locations which is mapped to Pocket
        */
        std::unordered_map<QString, std::unordered_map<QString, int>> m_recordsLocationsValueMap;
        /**
         * Record count mapped to locations which is mapped to Pocket
        */
        std::unordered_map<QString, std::unordered_map<QString, int>> m_recordsLocationsCountMap;

        /**
         * The QBarSeries which is created from the Records data
        */
        QBarSeries* m_barSeries;

        /**
         * Flag which indicates the usage of the ignore extremes function
        */
        bool m_ignoreExtremes = false;

        /**
         * Stringlist which contains the name of Pockets which has to be filtered
         * As default this list is empty
        */
        QStringList m_pocketFilter;

        /**
         * Records data display mode variable
         * The Records value is displayed as default
        */
        RecordsDataDisplayMode m_recordsDataDisplayMode = RecordsDataDisplayMode::RECORDS_VALUE;
        /**
         * Records data display type variable
         * The Records items are displayed as default
        */
        RecordsDataDisplayType m_recordsDataDisplayType = RecordsDataDisplayType::ITEM;

    private slots:
        /**
         * Called when the used changes the Records data display mode
         * through the corresponding chart modifier widget
        */
        void slot_changeRecordsDisplayMode();
        /**
         * Called when the used changes the Records data display type
         * through the corresponding chart modifier widget
        */
        void slot_changeRecordsDisplayType();

        /**
         * Called when a QBarSet is hovered
         * Shows and updated indicator QLabel for the hovered QBarSet's value
        */
        void slot_BarSetHoverChanged(bool status, int index);
    };
}

#endif // RECORDSDATACHARTVIEW_H
