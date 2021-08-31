#include "newrecordwidget.h"
#include "ui_newrecordwidget.h"
#include "Core/defines.h"
#include "Components/revertrecordwidget.h"

#include <QDateTime>
#include <QTimer>

namespace Content
{
    NewRecordWidget::NewRecordWidget(std::shared_ptr<User> user, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::NewRecordWidget),
        m_user(user)
    {
        ui->setupUi(this);

        initializeUi();
        initializeConnections();
    }

    NewRecordWidget::~NewRecordWidget()
    {
        delete ui;
    }

    void NewRecordWidget::initializeUi()
    {
        initializeRecordSettings();
        initializeDateTimeSettings();
    }

    void NewRecordWidget::initializeRecordSettings()
    {
        //Add a completer to the location and whatFor QLineEdits
        //using the User extracted location and whatFor data source
        ui->m_location_lineEdit->setCompleter(m_user->locationsCompleter());
        ui->m_whatFor_lineEdit->setCompleter(m_user->whatForsCompleter());
    }

    void NewRecordWidget::initializeDateTimeSettings()
    {
        //Get the current date and time and set the ui with this data
        const auto today = QDateTime::currentDateTime();

        const auto currentDate = today.date();
        ui->m_year_lineEdit->setText(QString::number(currentDate.year()));
        ui->m_month_lineEdit->setText(QString::number(currentDate.month()));
        ui->m_day_lineEdit->setText(QString::number(currentDate.day()));

        const auto currentTime = today.time();
        ui->m_hours_lineEdit->setText(QString::number(currentTime.hour()));
        ui->m_minutes_lineEdit->setText(QString::number(currentTime.minute()));
    }

    void NewRecordWidget::initializeConnections()
    {
        connect(ui->m_submit_btn, &QPushButton::clicked, this, &NewRecordWidget::slot_submit);
    }

    void NewRecordWidget::slot_submit()
    {
        //Get the amount value from the ui and check whether it is a valid integer
        //Set error style in case of error
        const auto amountString = ui->m_amount_lineEdit->text();
        bool amountOk = false;
        const auto amount = amountString.toInt(&amountOk);
        setLineEditErrorState(ui->m_amount_lineEdit, !amountOk);

        //Get the whatFor value from the ui and check whether it is a NOT empty QString
        //Set error style in case of error
        const auto whatFor = ui->m_whatFor_lineEdit->text();
        const auto whatForOk = !whatFor.isEmpty();
        setLineEditErrorState(ui->m_whatFor_lineEdit, !whatForOk);

        //Get the location value from the ui and check whether it is a NOT empty QString
        //Set error style in case of error
        const auto location = ui->m_location_lineEdit->text();
        const auto locationOk = !location.isEmpty();
        setLineEditErrorState(ui->m_location_lineEdit, !locationOk);

        //Get the year value and check whether it is an integer between 1997 and 2100
        //Set error style in case of error
        const auto yearString = ui->m_year_lineEdit->text();
        bool yearOk = false;
        const auto year = yearString.toInt(&yearOk);
        yearOk = (yearOk && year >= 1997 && year <= 2100);
        setLineEditErrorState(ui->m_year_lineEdit, !yearOk);

        //Get the month value and check whether it is an integer between 1 and 12
        //Set error style in case of error
        const auto monthString = ui->m_month_lineEdit->text();
        bool monthOk = false;
        const auto month = monthString.toInt(&monthOk);
        monthOk = (monthOk && month >= 01 && month <= 12);
        setLineEditErrorState(ui->m_month_lineEdit, !monthOk);

        //Get the day value and check whether it is an integer between 1 and 31
        //Set error style in case of error
        const auto dayString = ui->m_day_lineEdit->text();
        bool dayOk = false;
        const auto day = dayString.toInt(&dayOk);
        dayOk = (dayOk && day >= 01 && day <= 31);
        setLineEditErrorState(ui->m_day_lineEdit, !dayOk);

        //Get the hours value and check whether it is an integer between 0 and 23
        //Set error style in case of error
        const auto hoursString = ui->m_hours_lineEdit->text();
        bool hoursOk = false;
        const auto hours = hoursString.toInt(&hoursOk);
        hoursOk = (hoursOk && hours >= 00 && hours <= 23);
        setLineEditErrorState(ui->m_hours_lineEdit, !hoursOk);

        //Get the minutes value and check whether it is an integer between 0 and 59
        //Set error style in case of error
        const auto minutesString = ui->m_minutes_lineEdit->text();
        bool minutesOk = false;
        const auto minutes = minutesString.toInt(&minutesOk);
        minutesOk = (minutesOk && minutes >= 00 && minutes <= 59);
        setLineEditErrorState(ui->m_minutes_lineEdit, !minutesOk);

        //If the user given values are correct so far proceed with additional validation
        if(amountOk && whatForOk && locationOk &&
                yearOk && monthOk && dayOk &&
                hoursOk && minutesOk)
        {
            //Check whether the given date value is valid
            //Set error style in case of error
            const auto date = QDate(year, month, day);
            const auto isDateValid = date.isValid();
            setLineEditErrorState(ui->m_year_lineEdit, !isDateValid);
            setLineEditErrorState(ui->m_month_lineEdit, !isDateValid);
            setLineEditErrorState(ui->m_day_lineEdit, !isDateValid);

            //Check whether the given time value is valid
            //Set error style in case of error
            const auto time = QTime(hours, minutes);
            const auto isTimeValid = time.isValid();
            setLineEditErrorState(ui->m_hours_lineEdit, !isTimeValid);
            setLineEditErrorState(ui->m_minutes_lineEdit, !isTimeValid);

            //If the date and time values are correct create a RevertRecordWidget
            //which will schedule the Record persistence
            if(isDateValid && isTimeValid)
            {
                Component::RevertRecordWidget* revertRecordWidget =
                        new Component::RevertRecordWidget(Record(amount, date, time, location, whatFor), m_user, parentWidget()->parentWidget());

                revertRecordWidget->show();

                //Update the ui when the RevertRecordWidget finishes
                connect(revertRecordWidget, &QObject::destroyed, this, [=]
                {
                   initializeRecordSettings();
                });
            }
        }
    }
}
