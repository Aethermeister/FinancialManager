#ifndef POCKETSVALUECHARTVIEW_H
#define POCKETSVALUECHARTVIEW_H

#include "piechartview.h"
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
    */
    class LIB_EXPORT PocketsValueChartView : public PieChartView
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

    protected:
        /**
         * Show the needed series according to the currently set type(s)
        */
        virtual void showSelectedPieSeries() override;

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
         * Creates and returns the Pocket data display modifier widget
        */
        QWidget* createPocketTypeDisplayModifierWidget() const;

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
         * Called when the used changes the Pocket data display mode
         * through the corresponding chart modifier widget
        */
        void slot_changePocketTypeDisplay();
    };
}

#endif // POCKETSVALUECHARTVIEW_H
