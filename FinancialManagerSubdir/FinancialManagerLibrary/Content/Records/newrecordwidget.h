#ifndef NEWRECORDWIDGET_H
#define NEWRECORDWIDGET_H
#include "user.h"

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

namespace Ui {
class NewRecordWidget;
}

namespace Content::Records
{
    /**
     * Ui class which provides interactable interface for the user to create new Records
     * This class is responsible for correctly creating a new Record
    */
    class LIB_EXPORT NewRecordWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit NewRecordWidget(std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~NewRecordWidget();

        /**
         * Returns the new record widget's record value QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* recordValueLineEdit();
        /**
         * Returns the new record widget's record value QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* recordItemLineEdit();
        /**
         * Returns the new record widget's record location QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* recordLocationLineEdit();
        /**
         * Returns the new record widget's available pockets QComboBox
         * Used so test project(s) can access it
        */
        QComboBox* recordPocketComboBox();

        /**
         * Returns the new record widget's creation year QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* yearLineEdit();
        /**
         * Returns the new record widget's creation month QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* monthLineEdit();
        /**
         * Returns the new record widget's creation day QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* dayLineEdit();
        /**
         * Returns the new record widget's creation hours QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* hoursLineEdit();
        /**
         * Returns the new record widget's creation minutes QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* minutesLineEdit();

        /**
         * Returns the new record widget's submit QPushButton
         * Used so test project(s) can access it
        */
        QPushButton* submitRecordButton();

        /**
         * Returns the new record widget's record listing QWidget
         * Used so test project(s) can access it
        */
        QWidget* historyListingWidget();

    private:
        Ui::NewRecordWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();
        /**
         * Sets the initial state of the Record Settings section of this widget
        */
        void initializeRecordSettings();
        /**
         * Sets the initial state of the Date Time Settings section of this widget
        */
        void initializeDateTimeSettings();
        /**
         * Sets the common connections related to this class
        */
        void initializeConnections();

        /**
         * The current user
        */
        std::shared_ptr<User> m_user;

    private slots:
        /**
         * Called when the Submit QPushButton is clicked
         * Starts the new Record validation and persisting procedure
        */
        void slot_submit();
    };
}

#endif // NEWRECORDWIDGET_H
