#ifndef POCKETSVALUECHARTVIEW_H
#define POCKETSVALUECHARTVIEW_H

#include "chartviewbase.h"
#include "user.h"

namespace Content::Statistics::Components
{
    /**
     * Enum which holds the used pocket data type
    */
    enum PocketTypeDisplay
    {
        POCKET_VALUE,
        POCKET_USAGE
    };

    /**
     * Ui class which provides Pocket value and usage related information
     * Derived from ChartViewBase
    */
    class PocketsValueChartView : public ChartViewBase
    {
        Q_OBJECT
    public:
        explicit PocketsValueChartView(std::shared_ptr<User> user, QWidget* parent = Q_NULLPTR);
        ~PocketsValueChartView();

        /**
         * Creates the corresponding series for the Pocket value and usage
        */
        virtual void initializeSeries() override;
        /**
         * Creates the chart modifier widgets
        */
        virtual void initializeChartAdjustingWidgets() override;

    private:
        /**
         * Creates and returns the Pocket's value data series
        */
        QPieSeries* createPocketValueSeries() const;
        /**
         * Creates and returns the Pocket's usage data series
        */
        QPieSeries* createPocketUsageSeries() const;

        /**
         * Creates and returns the series slice display modifier widget
        */
        QWidget* createSliceValueDisplayModifierWidget() const;
        /**
         * Creates and returns the Pocket data display modifier widget
        */
        QWidget* createPocketTypeDisplayModifierWidget() const;

        /**
         * Show the needed series according to the currently set type
        */
        void showSelectedSeries();

        /**
         * Slice display mode variable
         * The value is displayed as default
        */
        SliceDisplayMode m_sliceDisplayMode = SliceDisplayMode::VALUE;
        /**
         * Pocket data display mode variable
         * The Pocket value is displayed as default
        */
        PocketTypeDisplay m_pocketTypeDisplay = PocketTypeDisplay::POCKET_VALUE;

        /**
         * A QPieSeries which is created from the Pocket values data
        */
        QPieSeries* m_pocketValueSeries;
        /**
         * A QPieSeries which is created from the Pocket usage data
        */
        QPieSeries* m_pocketUsageSeries;

    private slots:
        /**
         * Called when the used changes the slice display mode
         * through the corresponding chart modifier widget
        */
        void slot_changeSliceDisplayMode();
        /**
         * Called when the used changes the Pocket data display mode
         * through the corresponding chart modifier widget
        */
        void slot_changePocketTypeDisplay();
    };
}

#endif // POCKETSVALUECHARTVIEW_H
