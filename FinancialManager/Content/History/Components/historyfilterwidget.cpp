#include "historyfilterwidget.h"
#include "ui_historyfilterwidget.h"
#include "Core/defines.h"

#include <QStyleOption>
#include <QPainter>

namespace Content::History::Component
{
    HistoryFilterWidget::HistoryFilterWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::HistoryFilterWidget)
    {
        ui->setupUi(this);

        initializeConnections();
    }

    HistoryFilterWidget::~HistoryFilterWidget()
    {
        delete ui;
    }

    void HistoryFilterWidget::initializeConnections() const
    {
        //Connect every QLineEdits' editingFinished signal to the slot_validateFilter slot
        //So every filter change will run the filter value validation and on success emit the sig_filterHistory signal

        connect(ui->m_fromAmount_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);
        connect(ui->m_toAmount_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);

        connect(ui->m_item_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);
        connect(ui->m_location_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);

        connect(ui->m_fromYear_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);
        connect(ui->m_fromMonth_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);
        connect(ui->m_fromDay_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);

        connect(ui->m_toYear_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);
        connect(ui->m_toMonth_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);
        connect(ui->m_toDay_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);

        connect(ui->m_fromHours_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);
        connect(ui->m_fromMinutes_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);

        connect(ui->m_toHours_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);
        connect(ui->m_toMinutes_lineEdit, &QLineEdit::editingFinished, this, &HistoryFilterWidget::slot_validateFilter);
    }

    QString HistoryFilterWidget::validateAmountFilter(QLineEdit *amount_lineEdit, bool *ok) const
    {
        //Set the ok to true so when there is no actual filter value it is indicated normally but is ignored afterwards
        *ok = true;
        auto amount = amount_lineEdit->text();
        //Check whether there is an available filter value
        if(!amount.isEmpty())
        {
            //Check whether the filter value is an integer
            amount.toInt(ok);
            if(!*ok)
            {
                amount = QString();
            }
        }

        //Set the state of the corresponding QLineEdit
        setLineEditErrorState(amount_lineEdit, !*ok);

        return amount;
    }

    QDate HistoryFilterWidget::validateDateFilter(QLineEdit *year_lineEdit, QLineEdit *month_lineEdit, QLineEdit *day_lineEdit, bool *ok) const
    {
        //Get the QDate related information from the ui through the parameter given QLineEdits
        const auto yearString = year_lineEdit->text();
        const auto monthString = month_lineEdit->text();
        const auto dayString = day_lineEdit->text();

        //Check whether the raw QDate values are empty
        //If all three of them is empty than the actual QDate should be ignored
        //and no error indication should be shown
        if(yearString.isEmpty() && monthString.isEmpty() && dayString.isEmpty())
        {
            *ok = true;

            setLineEditErrorState(year_lineEdit, !*ok);
            setLineEditErrorState(month_lineEdit, !*ok);
            setLineEditErrorState(day_lineEdit, !*ok);

            return QDate();
        }

        //Convert the filter values to integer so an actual QDate value can be created
        const auto year = yearString.toInt();
        const auto month = monthString.toInt();
        const auto day = dayString.toInt();
        const auto date = QDate(year, month, day);

        //Check whether this new QDate filter value is valid or not
        //and set the ui error indication accordingly
        *ok = date.isValid();

        setLineEditErrorState(year_lineEdit, !*ok);
        setLineEditErrorState(month_lineEdit, !*ok);
        setLineEditErrorState(day_lineEdit, !*ok);

        if(*ok)
        {
            return date;
        }
        return QDate();
    }

    QTime HistoryFilterWidget::validateTimeFilter(QLineEdit *hours_lineEdit, QLineEdit *minutes_lineEdit, bool *ok) const
    {
        //Get the QTime related information from the ui through the parameter given QLineEdits
        const auto hoursString = hours_lineEdit->text();
        const auto minutesString = minutes_lineEdit->text();

        //Check whether the raw QTime values are empty
        //If both of them is empty than the actual QTime should be ignored
        //and no error indication should be shown
        if(hoursString.isEmpty() && minutesString.isEmpty())
        {
            *ok = true;

            setLineEditErrorState(hours_lineEdit, !*ok);
            setLineEditErrorState(minutes_lineEdit, !*ok);

            return QTime();
        }

        //First convert the hours and minutes values to integer and than create a QTime
        bool isHoursOk = true;
        const auto hours = hoursString.toInt(&isHoursOk);

        bool isMinutesOk = true;
        const auto minutes = minutesString.toInt(&isMinutesOk);

        //Check whether the hours and minutes values are actually integer values
        //and check whether the created QTime filter value is valid
        //and set the ui error indication accordingly
        const auto time = QTime(hours, minutes);
        *ok = isHoursOk && isMinutesOk && time.isValid();

        setLineEditErrorState(hours_lineEdit, !*ok);
        setLineEditErrorState(minutes_lineEdit, !*ok);

        if(*ok)
        {
            return time;
        }
        return QTime();
    }

    void HistoryFilterWidget::slot_validateFilter()
    {
        //Get the Amount filter values and the validation flags
        bool isFromAmountOk = true;
        const auto fromAmount = validateAmountFilter(ui->m_fromAmount_lineEdit, &isFromAmountOk);
        bool isToAmountOk = true;
        const auto toAmount = validateAmountFilter(ui->m_toAmount_lineEdit, &isToAmountOk);

        //The item and location filter values do not need any complex validation
        //These values are used in raw QString format
        const auto item = ui->m_item_lineEdit->text();
        const auto location = ui->m_location_lineEdit->text();

        //Get the Date filter values and the validation flags
        bool isFromDateOk = true;
        const auto fromDate = validateDateFilter(ui->m_fromYear_lineEdit, ui->m_fromMonth_lineEdit, ui->m_fromDay_lineEdit, &isFromDateOk);
        bool isToDateOk = true;
        const auto toDate = validateDateFilter(ui->m_toYear_lineEdit, ui->m_toMonth_lineEdit, ui->m_toDay_lineEdit, &isToDateOk);

        //Get the Time filter values and the validation flags
        bool isFromTimeOk = true;
        const auto fromTime = validateTimeFilter(ui->m_fromHours_lineEdit, ui->m_fromMinutes_lineEdit, &isFromTimeOk);
        bool isToTimeOk = true;
        const auto toTime = validateTimeFilter(ui->m_toHours_lineEdit, ui->m_toMinutes_lineEdit, &isToTimeOk);

        //If the validation flags are all true (validation successful)
        //Create a FilterData struct value and send it via signal to the RecordsHistoryWidget ui class
        if(isToAmountOk && isToDateOk && isToTimeOk &&
                isFromAmountOk && isFromDateOk && isFromTimeOk)
        {
            emit sig_filterHistory(FilterData(qMakePair(fromAmount, toAmount), qMakePair(fromDate, toDate),
                                              qMakePair(fromTime, toTime), std::move(item), std::move(location)));
        }

    }
}
