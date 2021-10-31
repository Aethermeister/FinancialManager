#include "statisticsselectionwidget.h"
#include "ui_statisticsselectionwidget.h"

namespace Content::Statistics
{
    StatisticsSelectionWidget::StatisticsSelectionWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::StatisticsSelectionWidget)
    {
        ui->setupUi(this);

        initializeConnections();
    }

    StatisticsSelectionWidget::~StatisticsSelectionWidget()
    {
        delete ui;
    }

    void StatisticsSelectionWidget::initializeConnections()
    {
        //Send the selected type via signal

        connect(ui->m_pocketValueAndUsage_btn, &QPushButton::clicked, [=]
        {
            emit sig_statisticsTypeSelected(StatisticsType::POCKET_VALUE_AND_USAGE);
        });

        connect(ui->m_recordsData_btn, &QPushButton::clicked, [=]
        {
            emit sig_statisticsTypeSelected(StatisticsType::RECORDS_DATA);
        });
    }
}
