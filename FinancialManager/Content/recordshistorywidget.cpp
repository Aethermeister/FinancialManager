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



        const auto records = m_user->records();
        for(const auto& record : records)
        {
            const auto historyItem = new Component::RecordHistoryItemWidget(record, ui->m_historyContainer_widget);
            ui->m_historyContainer_layout->addWidget(historyItem);

            connect(historyItem, &Component::RecordHistoryItemWidget::sig_recordItemClicked, [=](bool checked)
            {
                if(m_activeRecordItemWidget)
                {
                    m_activeRecordItemWidget->setChecked(false);
                    m_activeRecordItemWidget->setProperty("state", "normal");
                    updateWidgetStyle(m_activeRecordItemWidget);

                    m_activeRecordItemWidget = nullptr;
                }

                if(checked)
                {
                    m_activeRecordItemWidget = historyItem;
                }
            });
        }

        ui->m_historyContainer_layout->addItem(new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    }

    RecordsHistoryWidget::~RecordsHistoryWidget()
    {
        delete ui;
    }
}
