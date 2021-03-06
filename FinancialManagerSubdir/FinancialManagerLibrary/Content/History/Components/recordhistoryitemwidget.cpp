#include "recordhistoryitemwidget.h"
#include "ui_recordhistoryitemwidget.h"
#include "Core/defines.h"

#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>

namespace Content::History::Component
{
    RecordHistoryItemWidget::RecordHistoryItemWidget(const Content::Records::Record &record, bool isInteractive, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::RecordHistoryItemWidget),
        m_record(record),
        m_isInteractive(isInteractive)
    {
        ui->setupUi(this);

        initializeUi();
    }

    RecordHistoryItemWidget::~RecordHistoryItemWidget()
    {
        delete ui;
    }

    void RecordHistoryItemWidget::setMouseOver(bool isMouseOver)
    {
        m_isMouseOver = isMouseOver;
    }

    void RecordHistoryItemWidget::setChecked(bool checked)
    {
        m_isChecked = checked;
    }

    const Content::Records::Record& RecordHistoryItemWidget::record() const
    {
        return m_record;
    }

    void RecordHistoryItemWidget::paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event)

        //This method has to be overriden so the custom styling from the .qss file affects the ui

        QStyleOption o;
        o.initFrom(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
    }

    void RecordHistoryItemWidget::enterEvent(QEvent *event)
    {
        Q_UNUSED(event)

        //Check whether this widget is marked as interactive
        if(m_isInteractive)
        {
            //Set the m_isMouseOver flag to true since the Mouse pointer leaves the ui
            m_isMouseOver = true;
            //If the object is not pressed or checked set the ui style to hover
            if(!m_isPressed && !m_isChecked)
            {
                setWidgetStyleByProperty(this, "state", "hover");
            }
        }
    }

    void RecordHistoryItemWidget::leaveEvent(QEvent *event)
    {
        Q_UNUSED(event)

        //Check whether this widget is marked as interactive
        if(m_isInteractive)
        {
            //Set the m_isMouseOver flag to false since the Mouse pointer leaves the ui
            m_isMouseOver = false;
            //If the object is not pressed or checked set the ui style to normal
            if(!m_isPressed && !m_isChecked)
            {
                setWidgetStyleByProperty(this, "state", "normal");
            }
        }
    }

    void RecordHistoryItemWidget::mousePressEvent(QMouseEvent *event)
    {
        //Check whether this event was invoked by the Mouse Left button
        const auto pressedButton = event->button();
        if(pressedButton != Qt::LeftButton)
        {
            return;
        }

        //Check whether this widget is marked as interactive
        if(m_isInteractive)
        {
            //Set the m_isPressed flag to true since the Mouse Left button is pressed on the ui
            //and set the ui style to pressed
            m_isPressed = true;
            setWidgetStyleByProperty(this, "state", "pressed");
        }
    }

    void RecordHistoryItemWidget::mouseReleaseEvent(QMouseEvent *event)
    {
        //Check whether this event was invoked by the Mouse Left button
        const auto releasedButton = event->button();
        if(releasedButton != Qt::LeftButton)
        {
            return;
        }

        //Check whether this widget is marked as interactive
        if(m_isInteractive)
        {
            //Set the m_isPressed flag to true since the Mouse Left button is released on the ui
            m_isPressed = false;
            if(m_isMouseOver)
            {
                //Change the checked state
                m_isChecked = !m_isChecked;
                //Set the ui style according to the checked state
                if(m_isChecked)
                {
                    setWidgetStyleByProperty(this, "state", "checked");
                }
                else
                {
                    setWidgetStyleByProperty(this, "state", "hover");
                }

                emit sig_recordItemClicked(m_isChecked);
            }
            else
            {
                setWidgetStyleByProperty(this, "state", "normal");
            }
        }
    }

    void RecordHistoryItemWidget::initializeUi()
    {
        //Set the text of the value QLabel
        setLabelNegativeState(ui->m_value_lbl, m_record.value());

        //Show the creation date of the corresponding Record with the format below
        ui->m_date_lbl->setText(m_record.date().toString("yyyy.MM.dd."));

        //Elide the item text so it fitst the ui size
        const auto fontMetrics = ui->m_item_lbl->fontMetrics();
        const auto item = fontMetrics.elidedText(m_record.item(), Qt::ElideRight, width() - 100);
        ui->m_item_lbl->setText(item);
    }
}
