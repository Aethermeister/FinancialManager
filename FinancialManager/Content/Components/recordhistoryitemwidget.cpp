#include "recordhistoryitemwidget.h"
#include "ui_recordhistoryitemwidget.h"
#include "Core/defines.h"

#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>

namespace Content::Component
{
    RecordHistoryItemWidget::RecordHistoryItemWidget(Record record, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::RecordHistoryItemWidget),
        m_record(record)
    {
        ui->setupUi(this);

        initializeUi();
    }

    RecordHistoryItemWidget::~RecordHistoryItemWidget()
    {
        delete ui;
    }

    void RecordHistoryItemWidget::setChecked(bool checked)
    {
        m_isChecked = checked;
    }

    void RecordHistoryItemWidget::paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event);

        QStyleOption o;
        o.initFrom(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    }

    void RecordHistoryItemWidget::enterEvent(QEvent *event)
    {
        Q_UNUSED(event);

        m_isMouseOver = true;
        if(!m_isPressed && !m_isChecked)
        {
            setProperty("state", "hover");
            updateWidgetStyle(this);
        }
    }

    void RecordHistoryItemWidget::leaveEvent(QEvent *event)
    {
        Q_UNUSED(event);

        m_isMouseOver = false;
        if(!m_isPressed && !m_isChecked)
        {
            setProperty("state", "normal");
            updateWidgetStyle(this);
        }
    }

    void RecordHistoryItemWidget::mousePressEvent(QMouseEvent *event)
    {
        const auto releasedButton = event->button();
        if(releasedButton != Qt::LeftButton)
        {
            return;
        }

        m_isPressed = true;
        setProperty("state", "pressed");
        updateWidgetStyle(this);
    }

    void RecordHistoryItemWidget::mouseReleaseEvent(QMouseEvent *event)
    {
        const auto releasedButton = event->button();
        if(releasedButton != Qt::LeftButton)
        {
            return;
        }

        m_isPressed = false;
        if(m_isMouseOver)
        {
            m_isChecked = !m_isChecked;
            //emit signal
            if(m_isChecked)
            {
                setProperty("state", "checked");
                updateWidgetStyle(this);
            }
            else
            {
                setProperty("state", "hover");
                updateWidgetStyle(this);
            }

            emit sig_recordItemClicked(m_isChecked);
        }
        else
        {
            setProperty("state", "normal");
            updateWidgetStyle(this);
        }
    }

    void RecordHistoryItemWidget::initializeUi()
    {
        //Set the text of the amount QLabel
        setLabelNegativeState(ui->m_amount_lbl, m_record.Amount);

        ui->m_date_lbl->setText(m_record.Date.toString("yyyy.MM.dd."));

        const auto fontMetrics = ui->m_whatFor_lbl->fontMetrics();
        const auto whatFor = fontMetrics.elidedText(m_record.WhatFor, Qt::ElideRight, width() - 100);
        ui->m_whatFor_lbl->setText(whatFor);
    }
}
