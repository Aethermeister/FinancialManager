#ifndef RECORDSHISTORYWIDGET_H
#define RECORDSHISTORYWIDGET_H
#include "user.h"
#include "Components/recordhistoryitemwidget.h"
#include "Components/historyfilterwidget.h"
#include "Components/recordcontentwidget.h"

#include <QWidget>

namespace Ui {
class RecordsHistoryWidget;
}

namespace Content::History
{
    /**
     * Ui class which provides interactable interface for the user to manage the Records
     * This class is responsible for listing, filtering and managing the existing Records
    */
    class LIB_EXPORT RecordsHistoryWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit RecordsHistoryWidget(std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~RecordsHistoryWidget();

        /**
         * Returns the history widget's record listing QWidget
         * Used so test project(s) can access it
        */
        QWidget* historyListingWidget();

        QPushButton* filterButton();
        Component::HistoryFilterWidget* filterWidget();
        Component::RecordContentWidget* recordContentWidget();

    private:
        Ui::RecordsHistoryWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();
        /**
         * Sets the common connections related to this class
        */
        void initializeConnections() const;

        /**
         * Wraps the specific filtering methods
         * and returns their summarized results
        */
        bool filterRecord(const Content::Records::Record& record, const Component::FilterData& filterData);
        /**
         * Tests the parameter given value against the parameter given value filter
        */
        bool filterValue(int value, QPair<QString, QString> valueFilter);
        /**
         * Tests the parameter given date value against the parameter given date filter
        */
        bool filterDate(QDate date, QPair<QDate, QDate> dateFilter);
        /**
         * Tests the parameter given time value against the parameter given time filter
        */
        bool filterTime(QTime time, QPair<QTime, QTime> timeFilter);

        /**
         * The current user
        */
        std::shared_ptr<User> m_user;


    private slots:
        /**
         * Called when the user sets a filter
         * Adjusts the visibility of the Record items according to the filter
        */
        void slot_filterRecordsHistory(const Component::FilterData& filterData);

        /**
         * Called when the user clicks  the Delete Record button when one is selected
         * Removes the selected Record from the User data and from the ui
        */
        void slot_deleteSelectedRecord();
    };
}

#endif // RECORDSHISTORYWIDGET_H
