#include "historylistingwidget.h"
#include "Core/defines.h"
#include "recordhistoryitemwidget.h"
#include "ui_historylistingwidget.h"

namespace Content::History::Component
{
    HistoryListingWidget::HistoryListingWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::HistoryListingWidget)
    {
        ui->setupUi(this);
    }

    HistoryListingWidget::~HistoryListingWidget()
    {
        delete ui;
    }

    void HistoryListingWidget::initialize(std::shared_ptr<User> user, Component::RecordContentWidget *recordContentWidget)
    {
        connect(user.get(), &User::sig_recordAdded, this, &HistoryListingWidget::slot_newRecordAdded);
        connect(user.get(), &User::sig_recordDeleted, this, &HistoryListingWidget::slot_recordDeleted);

        //List the Records
        const auto records = user->records();

        //Show a message if there are no records
        if(records.empty())
        {
            showNoRecordMessage();
        }
        else
        {
            for(const auto& record : records)
            {
                //Create ui for the given record
                const auto historyItem = new Component::RecordHistoryItemWidget(record, true, this);
                ui->m_historyListing_layout->addWidget(historyItem);

                //Create connection to handle the item click signals
                connect(historyItem, &Component::RecordHistoryItemWidget::sig_recordItemClicked, this, [=](bool checked)
                {
                    //Reset the active/previously selected Record item
                    if(m_activeRecordItemWidget)
                    {
                        m_activeRecordItemWidget->setChecked(false);
                        setWidgetStyleByProperty(m_activeRecordItemWidget, "state", "normal");

                        m_activeRecordItemWidget = nullptr;
                    }

                    //If the sender Record item is checked set it as the new active Record item
                    if(checked)
                    {
                        recordContentWidget->initializeUi(record);
                        m_activeRecordItemWidget = historyItem;
                    }

                    //Show the Record Content Widget according to the checked state
                    recordContentWidget->setVisible(checked);
                });
            }
        }

        ui->m_historyListing_layout->addItem(new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    }

    void HistoryListingWidget::initialize(std::shared_ptr<User> user, int listedItemsCount)
    {
        connect(user.get(), &User::sig_recordAdded, this, &HistoryListingWidget::slot_newRecordAdded);
        connect(user.get(), &User::sig_recordDeleted, this, &HistoryListingWidget::slot_recordDeleted);

        //List the Records
        //Check whether there are enough records for the list counter
        //and reset the counter if it is originally over the records count
        const auto records = user->records();
        if(const auto recordSize = static_cast<int>(records.size()); listedItemsCount > recordSize)
        {
            listedItemsCount = recordSize;
        }

        //Show a message if there are no records
        if(records.empty())
        {
            showNoRecordMessage();
        }
        else
        {
            //Create ui for the first X (parameter given value) records
            for (int i = 0; i < listedItemsCount; i++)
            {
                const auto record = records.at(i);
                const auto historyItem = new Component::RecordHistoryItemWidget(record, false, this);
                ui->m_historyListing_layout->addWidget(historyItem);
            }
        }

        ui->m_historyListing_layout->addItem(new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    }

    RecordHistoryItemWidget *HistoryListingWidget::activeRecordItemWidget() const
    {
        return m_activeRecordItemWidget;
    }

    void HistoryListingWidget::setActiveRecordItemWidget(RecordHistoryItemWidget *recordItemWidget)
    {
        m_activeRecordItemWidget = recordItemWidget;
    }

    QList<RecordHistoryItemWidget *> HistoryListingWidget::recordItemWidgets() const
    {
        return findChildren<Component::RecordHistoryItemWidget*>();
    }

    void HistoryListingWidget::showNoRecordMessage()
    {
        //Create QLabel which shows the information if no Record is available
        QLabel *nothingToShow_label = new QLabel("Nothing to show", this);
        nothingToShow_label->setAlignment(Qt::AlignCenter);

        //Change the font style of the QLabel
        auto font = nothingToShow_label->font();
        font.setItalic(true);
        font.setBold(true);
        nothingToShow_label->setFont(font);

        ui->m_historyListing_layout->insertWidget(0, nothingToShow_label);
    }

    void HistoryListingWidget::slot_newRecordAdded(int index, const Content::Records::Record &record)
    {
        const auto historyItem = new Component::RecordHistoryItemWidget(record, false, this);
        ui->m_historyListing_layout->insertWidget(index, historyItem);
    }

    void HistoryListingWidget::slot_recordDeleted(const Content::Records::Record &record)
    {
        //Check whether there is a selected Record item and whether that item is the one being deleted
        if(m_activeRecordItemWidget)
        {
            if(m_activeRecordItemWidget->record() == record)
            {
                m_activeRecordItemWidget->deleteLater();
                m_activeRecordItemWidget = nullptr;
                return;
            }
        }

        //If there is no Record item selected or the selected one is not which is beind deleted
        //Iterate over the Record items and compare their Reocord object
        //Delete the Record item if it has the parameter given Record
        const auto recordItems = recordItemWidgets();
        for(const auto& recordItem : recordItems)
        {
            if(recordItem->record() == record)
            {
                recordItem->deleteLater();
                return;
            }
        }

        //If originally there was only one record than after deletion there is zero
        //Since there is zero record show the no record message
        if(recordItems.size() == 1)
        {
            showNoRecordMessage();
        }
    }
}
