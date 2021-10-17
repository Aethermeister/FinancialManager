#include "recordshistorywidget.h"
#include "ui_recordshistorywidget.h"
#include "Core/defines.h"

#include <QSpacerItem>

namespace Content::History
{
    RecordsHistoryWidget::RecordsHistoryWidget(std::shared_ptr<User> user, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::RecordsHistoryWidget),
        m_user(user)
    {
        ui->setupUi(this);

        initializeUi();
        initializeConnections();
    }

    RecordsHistoryWidget::~RecordsHistoryWidget()
    {
        delete ui;
    }

    void RecordsHistoryWidget::initializeUi()
    {
        ui->m_filter_widget->setVisible(false);
        ui->m_recordContent_widget->setVisible(false);

        //Initialize the Listing widget which contains the record items
        ui->m_historyListing_widget->initialize(m_user, ui->m_recordContent_widget);
    }

    void RecordsHistoryWidget::initializeConnections() const
    {
        connect(ui->m_filter_btn, &QPushButton::toggled, ui->m_filter_widget, &QWidget::setVisible);
        connect(ui->m_filter_widget, &Component::HistoryFilterWidget::sig_filterHistory, this, &RecordsHistoryWidget::slot_filterRecordsHistory);
        connect(ui->m_recordContent_widget, &Component::RecordContentWidget::sig_deleteRecord, this, &RecordsHistoryWidget::slot_deleteSelectedRecord);
    }

    bool RecordsHistoryWidget::filterRecord(const Content::Records::Record& record, const Component::FilterData& filterData)
    {
        //Call the specific filtering methods and store their results locally
        const auto isAmountOk = filterAmount(record.value(), filterData.AmountFilter);
        const auto isDateOk = filterDate(record.date(), filterData.DateFilter);
        const auto isTimeOk = isDateOk ? filterTime(record.time(), filterData.TimeFilter) : false;
        const auto isItemOk = record.item().contains(filterData.ItemFilter, Qt::CaseInsensitive);
        const auto isLocationOk = record.location().contains(filterData.LocationFilter, Qt::CaseInsensitive);

        //Return the summarized filter result
        //True: The corresponding Record item is visible
        return (isAmountOk && isDateOk && isTimeOk && isItemOk && isLocationOk);
    }

    bool RecordsHistoryWidget::filterAmount(int amount, QPair<QString, QString> amountFilter)
    {
        //Check the min/from amount filter value
        //Check whether the filter value is an empty QString
        //Empty QString means that the filter was not set and should be ignored
        bool isFromAmountOk = true;
        if(!amountFilter.first.isEmpty())
        {
            //Test the Record amount value agains the min/from filter
            const auto fromAmount = amountFilter.first.toInt();
            isFromAmountOk = amount >= fromAmount;
        }

        //Check the max/to amount filter value
        //Check whether the filter value is an empty QString
        //Empty QString means that the filter was not set and should be ignored
        bool isToAmountOk = true;
        if(!amountFilter.second.isEmpty())
        {
            //Test the Record amount value agains the max/to filter
            const auto toAmount = amountFilter.second.toInt();
            isToAmountOk = amount <= toAmount;
        }

        //Return the summarized amount filter result
        return (isFromAmountOk && isToAmountOk);
    }

    bool RecordsHistoryWidget::filterDate(QDate date, QPair<QDate, QDate> dateFilter)
    {
        //Check the min/from date filter value
        //Check whether the filter value is null
        //Null QDate means that the filter was not set and should be ignored
        bool isFromDateOk = true;
        if(!dateFilter.first.isNull())
        {
            //Test the Record date value agains the min/from filter
            isFromDateOk = date >= dateFilter.first;
        }

        //Check the max/to date filter value
        //Check whether the filter value is null
        //Null QDate means that the filter was not set and should be ignored
        bool isToDateOk = true;
        if(!dateFilter.second.isNull())
        {
            //Test the Record date value agains the max/to filter
            isToDateOk = date <= dateFilter.second;
        }

        //Return the summarized date filter result
        return (isFromDateOk && isToDateOk);
    }

    bool RecordsHistoryWidget::filterTime(QTime time, QPair<QTime, QTime> timeFilter)
    {
        //Check the min/from time filter value
        //Check whether the filter value is null
        //Null QTime means that the filter was not set and should be ignored
        bool isFromTimeOk = true;
        if(!timeFilter.first.isNull())
        {
            //Test the Record time value agains the min/from filter
            isFromTimeOk = time >= timeFilter.first;
        }

        //Check the max/to time filter value
        //Check whether the filter value is null
        //Null QTime means that the filter was not set and should be ignored
        bool isToTimeOk = true;
        if(!timeFilter.second.isNull())
        {
            //Test the Record time value agains the max/to filter
            isToTimeOk = time <= timeFilter.second;
        }

        //Return the summarized time filter result
        return (isFromTimeOk && isToTimeOk);
    }

    void RecordsHistoryWidget::slot_filterRecordsHistory(const Component::FilterData &filterData)
    {
        //Iterate over the existing Record items and run the filter on them
        const auto recordItems = ui->m_historyListing_widget->recordItemWidgets();
        for(auto &recordItem : recordItems)
        {
            //Set the visibility of the current Record item according to the filter results
            auto record = recordItem->record();
            const auto isRecordOk = filterRecord(record, filterData);

            recordItem->setVisible(isRecordOk);
        }
    }

    void RecordsHistoryWidget::slot_deleteSelectedRecord()
    {
        if(ui->m_historyListing_widget->activeRecordItemWidget())
        {
            //Through the User delete the selected Record
            const auto &selectedRecord = ui->m_historyListing_widget->activeRecordItemWidget()->record();
            m_user->deleteRecord(selectedRecord);

            ui->m_recordContent_widget->setVisible(false);
        }
    }
}
