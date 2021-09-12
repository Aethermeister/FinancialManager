#include "historylistingwidget.h"
#include "Core/defines.h"
#include "recordhistoryitemwidget.h"
#include "ui_historylistingwidget.h"

namespace Content::Component
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
        //List the Records
        const auto records = user->records();

        //Show a message if there are no records
        if(records.empty())
        {
            QLabel *nothingToShow_label = new QLabel("Nothing to show", this);
            ui->m_historyListing_layout->addWidget(nothingToShow_label);
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
        //List the Records
        //Check whether there are enough records for the list counter
        //and reset the counter if it is originally over the records count
        const auto records = user->records();
        if(const auto recordSize = records.size() - 1; listedItemsCount > recordSize)
        {
            listedItemsCount = recordSize;
        }

        //Show a message if there are no records
        if(records.empty())
        {
            QLabel *nothingToShow_label = new QLabel("Nothing to show", this);
            ui->m_historyListing_layout->addWidget(nothingToShow_label);
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
}
