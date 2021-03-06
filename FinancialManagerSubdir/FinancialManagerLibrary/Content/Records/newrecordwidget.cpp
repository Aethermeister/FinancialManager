#include "newrecordwidget.h"
#include "ui_newrecordwidget.h"
#include "Core/defines.h"
#include "Notification/revertrecordwidget.h"

#include <QDateTime>
#include <QTimer>

namespace Content::Records
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

    QLineEdit *NewRecordWidget::recordValueLineEdit()
    {
        return ui->m_value_lineEdit;
    }

    QLineEdit *NewRecordWidget::recordItemLineEdit()
    {
        return ui->m_item_lineEdit;
    }

    QLineEdit *NewRecordWidget::recordLocationLineEdit()
    {
        return ui->m_location_lineEdit;
    }

    QComboBox *NewRecordWidget::recordPocketComboBox()
    {
        return ui->m_pockets_comboBox;
    }

    QLineEdit *NewRecordWidget::yearLineEdit()
    {
        return ui->m_year_lineEdit;
    }

    QLineEdit *NewRecordWidget::monthLineEdit()
    {
        return ui->m_month_lineEdit;
    }

    QLineEdit *NewRecordWidget::dayLineEdit()
    {
        return ui->m_day_lineEdit;
    }

    QLineEdit *NewRecordWidget::hoursLineEdit()
    {
        return ui->m_hours_lineEdit;
    }

    QLineEdit *NewRecordWidget::minutesLineEdit()
    {
        return ui->m_minutes_lineEdit;
    }

    QPushButton *NewRecordWidget::submitRecordButton()
    {
        return ui->m_submit_btn;
    }

    QWidget *NewRecordWidget::historyListingWidget()
    {
        return ui->m_historyListing_widget;
    }

    void NewRecordWidget::initializeUi()
    {
        initializeRecordSettings();
        initializeDateTimeSettings();

        //Initialize the non-interactive Records history widget
        ui->m_historyListing_widget->initialize(m_user);
    }

    void NewRecordWidget::initializeRecordSettings()
    {
        //Add a completer to the location and item QLineEdits
        //using the User extracted location and item data source
        ui->m_location_lineEdit->setCompleter(m_user->locationsCompleter());
        ui->m_item_lineEdit->setCompleter(m_user->itemsCompleter());

        //Setup the pockets combobox
        ui->m_pockets_comboBox->clear();
        ui->m_pockets_comboBox->setEditable(true);
        ui->m_pockets_comboBox->lineEdit()->setReadOnly(true);
        ui->m_pockets_comboBox->lineEdit()->setAlignment(Qt::AlignCenter);
        ui->m_pockets_comboBox->lineEdit()->setPlaceholderText("Select Pocket");

        //Populate the pockets combobox
        QStringList pockets;
        for(const auto& pocket : m_user->pockets())
        {
            pockets << pocket.name();
        }

        ui->m_pockets_comboBox->addItems(pockets);
        ui->m_pockets_comboBox->setCurrentIndex(-1);
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
        //Get the value from the ui and check whether it is a valid integer
        //Set error style in case of error
        const auto valueString = ui->m_value_lineEdit->text();
        bool valueOk = false;
        const auto value = valueString.toInt(&valueOk);
        setWidgetErrorState(ui->m_value_lineEdit, !valueOk);

        //Get the item value from the ui and check whether it is a NOT empty QString
        //Set error style in case of error
        const auto item = ui->m_item_lineEdit->text();
        const auto itemOk = !item.isEmpty();
        setWidgetErrorState(ui->m_item_lineEdit, !itemOk);

        //Get the location value from the ui and check whether it is a NOT empty QString
        //Set error style in case of error
        const auto location = ui->m_location_lineEdit->text();
        const auto locationOk = !location.isEmpty();
        setWidgetErrorState(ui->m_location_lineEdit, !locationOk);

        //Get the pocket name value from the ui and check whether it is a NOT empty QString
        //Set error style in case of error
        const auto pocketName = ui->m_pockets_comboBox->currentText();
        const auto pocketNameOk = !pocketName.isEmpty();
        setWidgetErrorState(ui->m_pockets_comboBox, !pocketNameOk);

        //Get the year value and check whether it is an integer between 1997 and 2100
        //Set error style in case of error
        const auto yearString = ui->m_year_lineEdit->text();
        bool yearOk = false;
        const auto year = yearString.toInt(&yearOk);
        yearOk = (yearOk && year >= 1997 && year <= 2100);
        setWidgetErrorState(ui->m_year_lineEdit, !yearOk);

        //Get the month value and check whether it is an integer between 1 and 12
        //Set error style in case of error
        const auto monthString = ui->m_month_lineEdit->text();
        bool monthOk = false;
        const auto month = monthString.toInt(&monthOk);
        monthOk = (monthOk && month >= 01 && month <= 12);
        setWidgetErrorState(ui->m_month_lineEdit, !monthOk);

        //Get the day value and check whether it is an integer between 1 and 31
        //Set error style in case of error
        const auto dayString = ui->m_day_lineEdit->text();
        bool dayOk = false;
        const auto day = dayString.toInt(&dayOk);
        dayOk = (dayOk && day >= 01 && day <= 31);
        setWidgetErrorState(ui->m_day_lineEdit, !dayOk);

        //Get the hours value and check whether it is an integer between 0 and 23
        //Set error style in case of error
        const auto hoursString = ui->m_hours_lineEdit->text();
        bool hoursOk = false;
        const auto hours = hoursString.toInt(&hoursOk);
        hoursOk = (hoursOk && hours >= 00 && hours <= 23);
        setWidgetErrorState(ui->m_hours_lineEdit, !hoursOk);

        //Get the minutes value and check whether it is an integer between 0 and 59
        //Set error style in case of error
        const auto minutesString = ui->m_minutes_lineEdit->text();
        bool minutesOk = false;
        const auto minutes = minutesString.toInt(&minutesOk);
        minutesOk = (minutesOk && minutes >= 00 && minutes <= 59);
        setWidgetErrorState(ui->m_minutes_lineEdit, !minutesOk);

        //If the user given values are correct so far proceed with additional validation
        if(valueOk && itemOk && locationOk && pocketNameOk &&
                yearOk && monthOk && dayOk && hoursOk && minutesOk)
        {
            //Check whether the given date value is valid
            //Set error style in case of error
            const auto date = QDate(year, month, day);
            const auto isDateValid = date.isValid();
            setWidgetErrorState(ui->m_year_lineEdit, !isDateValid);
            setWidgetErrorState(ui->m_month_lineEdit, !isDateValid);
            setWidgetErrorState(ui->m_day_lineEdit, !isDateValid);

            //Check whether the given time value is valid
            //Set error style in case of error
            const auto time = QTime(hours, minutes);
            const auto isTimeValid = time.isValid();
            setWidgetErrorState(ui->m_hours_lineEdit, !isTimeValid);
            setWidgetErrorState(ui->m_minutes_lineEdit, !isTimeValid);

            //If the date and time values are correct create a RevertRecordWidget
            //which will schedule the Record persistence
            if(isDateValid && isTimeValid && parentWidget())
            {
                Notification::RevertRecordWidget* revertRecordWidget =
                        new Notification::RevertRecordWidget({value, date, time, location, item, pocketName}, m_user, parentWidget()->parentWidget());

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
