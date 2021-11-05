#ifndef CONTENT_STATISTICS_COMPONENTS_PIECHARTVIEW_H
#define CONTENT_STATISTICS_COMPONENTS_PIECHARTVIEW_H

#include "chartviewbase.h"
#include "user.h"

namespace Content::Statistics::Components
{
    /**
     * Enum which holds values to change the QPieSeries slice display
    */
    enum SliceDisplayMode
    {
        VALUE,
        PERCENTAGE
    };

    /**
     * Base class of teh QPieSeries containing charts
    */
    class PieChartView : public ChartViewBase
    {
        Q_OBJECT
    public:
        PieChartView(std::shared_ptr<User> user, QWidget *parent = Q_NULLPTR);

    protected:
        /**
         * Show the needed series according to the currently set type
        */
        virtual void showSelectedPieSeries() = 0;

        /**
         * Creates and returns the series slice display modifier widget
        */
        QWidget* createSliceValueDisplayModifierWidget() const;

        /**
         * Slice display mode variable
         * The value is displayed as default
        */
        SliceDisplayMode m_sliceDisplayMode = SliceDisplayMode::VALUE;

    private slots:
        /**
         * Called when the used changes the slice display mode
         * through the corresponding chart modifier widget
        */
        void slot_changeSliceDisplayMode();
    };
}

#endif // CONTENT_STATISTICS_COMPONENTS_PIECHARTVIEW_H
