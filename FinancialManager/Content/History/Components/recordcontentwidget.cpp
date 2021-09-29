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

    void RecordContentWidget::initializeUi(const Record &selectedRecord)
    {
        //Set the ui so the details of the parameter given Record are listed
        setLabelNegativeState(ui->m_amount_lbl, selectedRecord.Amount);
        ui->m_whatFor_lbl->setText(selectedRecord.WhatFor);
        ui->m_location_lbl->setText(selectedRecord.Location);
        ui->m_date_lbl->setText(selectedRecord.Date.toString("yyyy. MMMM dd. (dddd)"));
        ui->m_time_lbl->setText(selectedRecord.Time.toString("HH:mm"));
    }

    void RecordContentWidget::initializeConnections() const
    {
        connect(ui->m_deleteRecord_btn, &QPushButton::clicked, this, &RecordContentWidget::sig_deleteRecord);
    }
}
