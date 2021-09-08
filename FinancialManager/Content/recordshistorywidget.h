#ifndef RECORDSHISTORYWIDGET_H
#define RECORDSHISTORYWIDGET_H
#include "user.h"
#include "Components/recordhistoryitemwidget.h"
#include "Components/historyfilterwidget.h"

#include <QWidget>

namespace Ui {
class RecordsHistoryWidget;
}

namespace Content
{
    /**
     * Ui class which provides interactable interface for the user to manage the Records
     * This class is responsible for listing, filtering and managing the existing Records
    */
    class RecordsHistoryWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit RecordsHistoryWidget(std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~RecordsHistoryWidget();

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
        bool filterRecord(Record record, Component::FilterData filterData);
        /**
         * Tests the parameter given amount value against the parameter given amount filter
        */
        bool filterAmount(int amount, QPair<QString, QString> amountFilter);
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
        /**
         * The currently selected Record item
         * It is initialized with nullptr because there is no selection at the beginning
        */
        Component::RecordHistoryItemWidget* m_activeRecordItemWidget = nullptr;

    private slots:
        /**
         * Called when the user sets a filter
         * Adjusts the visibility of the Record items according to the filter
        */
        void slot_filterRecordsHistory(Component::FilterData filterData);

        /**
         * Called when the user clicks  the Delete Record button when one is selected
         * Removes the selected Record from the User data and from the ui
        */
        void slot_deleteSelectedRecord();
    };
}

#endif // RECORDSHISTORYWIDGET_H
