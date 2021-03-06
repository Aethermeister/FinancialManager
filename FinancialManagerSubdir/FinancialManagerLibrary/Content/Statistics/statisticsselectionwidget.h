#ifndef STATISTICSSELECTIONWIDGET_H
#define STATISTICSSELECTIONWIDGET_H
#include "Core/global_defines.h"

#include <QWidget>
#include <QPushButton>

namespace Ui {
class StatisticsSelectionWidget;
}

namespace Content::Statistics
{
    /**
     * Enum which holds type values for the statistics widget selection
     * After selecting a statistics widget
     * one of these enum values are used to create the needed statistics widget
    */
    enum StatisticsType
    {
        CASH_FLOW,
        POCKET_VALUE_AND_USAGE,
        RECORDS_DATA
    };

    /**
     * This Ui class provides options to select a preferred statistics widget
    */
    class LIB_EXPORT StatisticsSelectionWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit StatisticsSelectionWidget(QWidget *parent = nullptr);
        ~StatisticsSelectionWidget();

        QPushButton* cashFlowButton();
        QPushButton* pocketValueAndUsageButton();
        QPushButton* recordsDataButton();

    private:
        Ui::StatisticsSelectionWidget *ui;

        /**
         * Sets the common connections related to this class
        */
        void initializeConnections();

    signals:
        /**
         * Signal emitted when the user selects one of the available options
         * The parameter given type indicates which statistics widget is selected
        */
        void sig_statisticsTypeSelected(Content::Statistics::StatisticsType type);
    };
}

#endif // STATISTICSSELECTIONWIDGET_H
