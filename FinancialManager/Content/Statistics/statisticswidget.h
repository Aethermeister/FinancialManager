#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H
#include "user.h"
#include "statisticsselectionwidget.h"

#include <QWidget>

namespace Ui {
class StatisticsWidget;
}

namespace Content::Statistics
{
    /**
     * This is the main widget for the other statistics related Ui classes
     * It contains a controller for chart selection and contains the selected charts
    */
    class StatisticsWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit StatisticsWidget(std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~StatisticsWidget();

    private:
        Ui::StatisticsWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();
        /**
         * Sets the common connections related to this class
        */
        void initializeConnections() const;

        /**
         * Shows the selected chart widget in the content area
        */
        void showStatisticsSelectionWidget();
        /**
         * Shows the chart which indicates the pocket values and usages
        */
        void showPocketValueStatisticsWidget();

        /**
         * The current user
        */
        std::shared_ptr<User> m_user;

    private slots:
        /**
         * Called when the user selects one of the available chart options
         * Replaces this selection widget with the selected chart widget
         * The parameter given type indicates which widget is selected
        */
        void slot_showSelectedStatisticsWidget(Content::Statistics::StatisticsType type);
    };
}

#endif // STATISTICSWIDGET_H
