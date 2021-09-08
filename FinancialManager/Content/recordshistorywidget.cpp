#include "recordshistorywidget.h"
#include "ui_recordshistorywidget.h"
#include "Core/defines.h"


#include <QSpacerItem>

namespace Content
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

        //List the Records
        const auto records = m_user->records();
        for(const auto& record : records)
        {
            //Create ui for the given record
            const auto historyItem = new Component::RecordHistoryItemWidget(record, ui->m_historyContainer_widget);
            ui->m_historyContainer_layout->addWidget(historyItem);

            //Create connection to handle the item click signals
            connect(historyItem, &Component::RecordHistoryItemWidget::sig_recordItemClicked, this, [=](bool checked)
            {
                //Reset the active/previously selected Record item
                if(m_activeRecordItemWidget)
                {
                    m_activeRecordItemWidget->setChecked(false);
                    m_activeRecordItemWidget->setProperty("state", "normal");
                    updateWidgetStyle(m_activeRecordItemWidget);

                    m_activeRecordItemWidget = nullptr;
                }

                //If the sender Record item is checked set it as the new active Record item
                if(checked)
                {
                    ui->m_recordContent_widget->initializeUi(record);
                    m_activeRecordItemWidget = historyItem;
                }

                ui->m_recordContent_widget->setVisible(checked);
            });
        }

        ui->m_historyContainer_layout->addItem(new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    }

    void RecordsHistoryWidget::initializeConnections() const
    {
        connect(ui->m_filter_btn, &QPushButton::toggled, ui->m_filter_widget, &QWidget::setVisible);
        connect(ui->m_filter_widget, &Component::HistoryFilterWidget::sig_filterHistory, this, &RecordsHistoryWidget::slot_filterRecordsHistory);
        connect(ui->m_recordContent_widget, &Component::RecordContentWidget::sig_deleteRecord, this, &RecordsHistoryWidget::slot_deleteSelectedRecord);
    }

    bool RecordsHistoryWidget::filterRecord(Record record, Component::FilterData filterData)
    {
        //Call the specific filtering methods and store their results locally
        const auto isAmountOk = filterAmount(record.Amount, filterData.AmountFilter);
        const auto isDateOk = filterDate(record.Date, filterData.DateFilter);
        const auto isTimeOk = isDateOk ? filterTime(record.Time, filterData.TimeFilter) : false;
        const auto isWhatForOk = record.WhatFor.contains(filterData.WhatForFilter, Qt::CaseInsensitive);
        const auto isLocationOk = record.Location.contains(filterData.LocationFilter, Qt::CaseInsensitive);

        //Return the summarized filter result
        //True: The corresponding Record item is visible
        return (isAmountOk && isDateOk && isTimeOk && isWhatForOk && isLocationOk);
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

    void RecordsHistoryWidget::slot_filterRecordsHistory(Component::FilterData filterData)
    {
        //Iterate over the existing Record items and run the filter on them
        const auto recordItems = ui->m_historyContainer_widget->findChildren<Component::RecordHistoryItemWidget*>();
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
        if(m_activeRecordItemWidget)
        {
            //Through the User delete the selected Record
            const auto &selectedRecord = m_activeRecordItemWidget->record();
            m_user->deleteRecord(selectedRecord);

            //Remove the Record related item from the ui
            m_activeRecordItemWidget->deleteLater();
            m_activeRecordItemWidget = nullptr;
        }
    }
}
