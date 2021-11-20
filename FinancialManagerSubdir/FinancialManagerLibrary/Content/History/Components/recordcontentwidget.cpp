#include "recordcontentwidget.h"
#include "ui_recordcontentwidget.h"
#include "Core/defines.h"

namespace Content::History::Component
{
    RecordContentWidget::RecordContentWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::RecordContentWidget)
    {
        ui->setupUi(this);

        initializeConnections();
    }

    RecordContentWidget::~RecordContentWidget()
    {
        delete ui;
    }

    QPushButton *RecordContentWidget::deleteRecordButton()
    {
        return ui->m_deleteRecord_btn;
    }

    void RecordContentWidget::initializeUi(const Content::Records::Record &selectedRecord)
    {
        //Set the ui so the details of the parameter given Record are listed
        setLabelNegativeState(ui->m_value_lbl, selectedRecord.value());
        ui->m_item_lbl->setText(selectedRecord.item());
        ui->m_location_lbl->setText(selectedRecord.location());
        ui->m_pocket_lbl->setText(selectedRecord.pocketName());

        ui->m_date_lbl->setText(selectedRecord.date().toString("yyyy. MMMM dd. (dddd)"));
        ui->m_time_lbl->setText(selectedRecord.time().toString("HH:mm"));
    }

    void RecordContentWidget::initializeConnections() const
    {
        connect(ui->m_deleteRecord_btn, &QPushButton::clicked, this, &RecordContentWidget::sig_deleteRecord);
    }
}
