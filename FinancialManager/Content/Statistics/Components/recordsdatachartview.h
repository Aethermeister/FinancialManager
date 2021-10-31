#ifndef RECORDSDATACHARTVIEW_H
#define RECORDSDATACHARTVIEW_H

#include "piechartview.h"

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
    class RecordsDataChartView : public PieChartView
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

    protected:
        /**
         * Show the needed series according to the currently set type(s)
        */
        virtual void showSelectedPieSeries() override;

    private:
        /**
         * Creates a menu which lists the Pockets and provides filtering option for them
        */
        QPushButton* createPocketFilterButton();
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
         * Changes the displayed label of each slice of the parameter given series
         * according to the currently set slice display mode
        */
        void adjustSeriesDisplay(QPieSeries* series);

        /**
         * Creates and return one summarized map according to the currently set display mode/type and filter
        */
        std::unordered_map<QString, int> summarizeRecordsData();
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
    };
}

#endif // RECORDSDATACHARTVIEW_H
