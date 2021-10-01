#ifndef HISTORYFILTERWIDGET_H
#define HISTORYFILTERWIDGET_H

#include <QWidget>
#include <QPair>
#include <QDate>
#include <QTime>
#include <QLineEdit>

namespace Ui {
class HistoryFilterWidget;
}

namespace Content::History::Component
{
    /**
     * This struct is a wrapper for the filter related data
     * It is used by the RecordsHistoryWidget class to filter the listed Records
    */
    struct FilterData
    {
    public:
        FilterData(QPair<QString, QString> amountFilter, QPair<QDate, QDate> dateFilter, QPair<QTime, QTime> timeFilter,
                   const QString &itemFilter, const QString &locationFilter) :
            AmountFilter(amountFilter), DateFilter(dateFilter), TimeFilter(timeFilter),
            ItemFilter(itemFilter), LocationFilter(locationFilter)
        {

        }

        /**
         * This QPair holds the min and max (QString) Amount values in between the Records should be listed
         * Note that QString is used for the amount so it can be easily determined whether there is an inputed value
         * Given Record Amount value is tested against both first and second QPair values
        */
        QPair<QString, QString> AmountFilter;
        /**
         * This QPair holds the min and max (QDate) Date values in between the Records should be listed
         * Given record Date value is tested against bothe first and second QPair values
        */
        QPair<QDate, QDate> DateFilter;
        /**
         * This QPair holds the min and max (QTime) Time values in between the Records should be listed
         * Given record Time value is tested against bothe first and second QPair values
        */
        QPair<QTime, QTime> TimeFilter;
        /**
         * This QString holds the data the user is filtering/searching for
         * Given Record Item value is tested whether that value contains this filter value or not
        */
        QString ItemFilter;
        /**
         * This QString holds the data the user is filtering/searching for
         * Given Record Location value is tested whether that value contains this filter value or not
        */
        QString LocationFilter;
    };

    /**
     * Ui class which provides basic filtering options for the Records listed in the RecordsHistoryWidget ui class
     * This class is responsible for validating the user given filter values and
     * sending them to the RecordsHistoryWidget class for further calculations
    */
    class HistoryFilterWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit HistoryFilterWidget(QWidget *parent = nullptr);
        ~HistoryFilterWidget();

    private:
        Ui::HistoryFilterWidget *ui;

        /**
         * Sets the common connections related to this class
        */
        void initializeConnections() const;

        /**
         * Validates the Amount filter value of the parameter given QLineEdit
         * and sets the parameter given bool pointer according to the validation result
        */
        QString validateAmountFilter(QLineEdit *amount_lineEdit, bool *ok) const;
        /**
         * Validates the Date filter value of the parameter given QLineEdit
         * and sets the parameter given bool pointer according to the validation result
        */
        QDate validateDateFilter(QLineEdit *year_lineEdit, QLineEdit *month_lineEdit, QLineEdit *day_lineEdit, bool *ok) const;
        /**
         * Validates the Time filter value of the parameter given QLineEdit
         * and sets the parameter given bool pointer according to the validation result
        */
        QTime validateTimeFilter(QLineEdit *hours_lineEdit, QLineEdit *minutes_lineEdit, bool *ok) const;

    private slots:
        /**
         * Called when a filter QLineEdit emits an editingFinished signal
         * Wraps the different filter validation methods
         * Emits the sig_filterHistory signal if the filter validation is successful
        */
        void slot_validateFilter();

    signals:
        /**
         * Emitted when the user sets a filter value
         * and the validation of the filter values are successful
        */
        void sig_filterHistory(const Content::History::Component::FilterData &filterData);
    };
}

#endif // HISTORYFILTERWIDGET_H
